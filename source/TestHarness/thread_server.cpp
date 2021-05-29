// socket_w_threadpool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "thread_server.h"
#include "TestExecutor.h"
#include <thread> // std::thread
#include <vector> // std::vector
#include <queue> // std::queue
#include <mutex> // std::mutex
#include <condition_variable> // std::condition_variable
#include "WS2tcpip.h"
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout

using namespace std;
#define DEFAULT_PORT "444"

// This class manages a thread pool that will process requests
class thread_pool {
public:
    thread_pool() : done(false) {
        // This returns the number of threads supported by the system. If the
        // function can't figure out this information, it returns 0. 0 is not good,
        // so we create at least 1
        auto numberOfThreads = std::thread::hardware_concurrency();
        if (numberOfThreads == 0) {
            numberOfThreads = 1;
        }

        for (unsigned i = 0; i < numberOfThreads; ++i) {
            // The threads will execute the private member `doWork`. Note that we need
            // to pass a reference to the function (namespaced with the class name) as
            // the first argument, and the current object as second argument
            threads.push_back(std::thread(&thread_pool::doWork, this));
        }
    }

    // The destructor joins all the threads so the program can exit gracefully.
    // This will be executed if there is any exception (e.g. creating the threads)
    ~thread_pool() {
        // So threads know it's time to shut down
        done = true;

        // Wake up all the threads, so they can finish and be joined
        workQueueConditionVariable.notify_all();
        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    // This function will be called by the server, every time there is a request
    // that needs to be processed by the thread pool
    void queueWork(int fd, std::string& request) {
        // Grab the mutex
        std::lock_guard<std::mutex> g(workQueueMutex);

        // Push the request to the queue
        workQueue.push(std::pair<int, std::string>(fd, request));

        // Notify one thread that there are requests to process
        workQueueConditionVariable.notify_one();
    }

private:
    // This condition variable is used for the threads to wait until there is work
    // to do
    std::condition_variable_any workQueueConditionVariable;

    // We store the threads in a vector, so we can later stop them gracefully
    std::vector<std::thread> threads;

    // Mutex to protect workQueue
    std::mutex workQueueMutex;

    // Queue of requests waiting to be processed
    std::queue<std::pair<int, std::string>> workQueue;

    // This will be set to true when the thread pool is shutting down. This tells
    // the threads to stop looping and finish
    bool done;

    // Function used by the threads to grab work from the queue
    void doWork() {
        // Loop while the queue is not destructing
        while (!done) {
            std::pair<int, std::string> request;

            // Create a scope, so we don't lock the queue for longer than necessary
            {
                std::unique_lock<std::mutex> g(workQueueMutex);
                workQueueConditionVariable.wait(g, [&] {
                    // Only wake up if there are elements in the queue or the program is
                    // shutting down
                    return !workQueue.empty() || done;
                    });

                request = workQueue.front();
                workQueue.pop();
            }

            processRequest(request);
        }
    }

    void processRequest(const std::pair<int, std::string> item) {
        // Pretend we are doing a lot of work
        std::this_thread::sleep_for(std::chrono::seconds(5));
        int maxLoggingLevel = 3;
        Logger logptr(3);
        TestExecutor* task1ptr = new TestExecutor;
        TestResponse response;
        response=task1ptr->Execute();
        logptr.Log(response);

        // Send a message to the connection
        const char* messresp = "test accepted";
        send(item.first, messresp, (int)strlen(messresp), 0);
        std::cout << "test run performed on : " << item.second << "\n";
        // Close the connection
        // closesocket(item.first);
    }
};

int main() {
    
    const char *connect_ok = "message_rcvd_by_server";
    const char* sendtest = "Test Request";
    
    long SUCCESSFUL;
    WSADATA wsaData;
    WORD DLLVERSION;

    //Create WORD value to set version 22
    DLLVERSION = MAKEWORD(2, 2);

    //Start WinSock DLL
    SUCCESSFUL = WSAStartup(DLLVERSION, &wsaData);

    struct addrinfo* result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
   
    // Resolve the local address and port to be used by the server
    int iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ListenSocket = INVALID_SOCKET;

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    SOCKET ClientSocket;
    ClientSocket = INVALID_SOCKET;

    // start the threadpool
    thread_pool tp;
    
    while (true) {
        char recvbuf[512] = { 0 }; // clear buffer
        std::string request = recvbuf;
        int recvbuflen = 512;
        int iResult, iSendResult;
        // Grab a connection from the queue
        cout << "\n\tSERVER:  Waiting for incoming connection...\n";
        ClientSocket = accept(ListenSocket, NULL, NULL);

        do {
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {
                printf("Bytes received: %d\n", iResult);
                // Echo message received ok
                iSendResult = send(ClientSocket, connect_ok, (int)strlen(connect_ok), 0);
                printf("Bytes sent: %d\n", iSendResult);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    //return 1;
                }
            }
            else if (iResult == 0) {
                printf("Connection closing...\n");
            }
            else {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                //return 1;
            }
            if (std::strcmp(recvbuf, sendtest) == 0) {  // if it's a test request...send to queue
                std::string request = recvbuf;
                tp.queueWork(ClientSocket, request);
            }
        } while (iResult > 0);
    }   
    closesocket(ListenSocket);
}