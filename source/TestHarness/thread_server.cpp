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
#include "iTestable.h"
#include "TestProfileLibrary.h"
#include "JsonMessageGenerator.h"
#include <map>

using namespace std;
#define DEFAULT_PORT "1337"

// This class manages a thread pool that will process requests
class thread_pool {
public:
    thread_pool() : done(false) {
        // This returns the number of threads supported by the system. If the
        // function can't figure out this information, it returns 0. 0 is not good,
        // so we create at least 1
        auto numberOfThreads = std::thread::hardware_concurrency();
        //int numberOfThreads = 4;
        cout << numberOfThreads << "-test threads have been started\n";
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
        cout << request << "-sent to workqueue \n";
        //std::lock_guard<std::mutex> g(workQueueMutex);

        // Push the request to the queue
        threadMutex.lock();
        workQueue.push(std::pair<int, std::string>(fd, request));
        threadMutex.unlock();

        // Notify one thread that there are requests to process
        workQueueConditionVariable.notify_all();
    }

    void setAvailableClassesToTest(std::vector<iTestable*> inpClassesToTest)
    {
        std::map<std::string, iTestable*> newAvailableClasses;

        for (iTestable* testable : inpClassesToTest)
        {
            newAvailableClasses[testable->GetTypeName()] = testable;
        }

        availableClassesToTest = newAvailableClasses;
    }

    std::map<std::string, iTestable*> getAvailableClassesToTest()
    {
        return availableClassesToTest;
    }

private:
    // This condition variable is used for the threads to wait until there is work
    // to do
    std::condition_variable_any workQueueConditionVariable;

    // We store the threads in a vector, so we can later stop them gracefully
    std::vector<std::thread> threads;

    // Mutex to protect workQueue
    std::mutex workQueueMutex;
    std::mutex threadMutex;

    // Queue of requests waiting to be processed
    std::queue<std::pair<int, std::string>> workQueue;

    // Library of possible classes to test
    std::map<std::string, iTestable*> availableClassesToTest;

    //address that we are running from (for message purposes)
    std::string sourceAddress;

    // This will be set to true when the thread pool is shutting down. This tells
    // the threads to stop looping and finish
    bool done;

    // Function used by the threads to grab work from the queue
    void doWork() {
        // Loop while the queue is not destructing
        while (!done) {
            cout << "\n  thread id = " << std::this_thread::get_id() << " is waiting for work \n";
            std::unique_lock<std::mutex> lck(workQueueMutex);
            workQueueConditionVariable.wait(lck);
            
            // Only wake up if there are elements in the queue or the program is shutting down
            std::pair<int, std::string> request;
            // check if workqueue is empty
            if (!workQueue.empty()) {
                threadMutex.lock();
                request = workQueue.front();
                workQueue.pop();
                threadMutex.unlock();
                cout << "\n  thread id = " << std::this_thread::get_id() << " is working on " << request.second << "\n";
                processRequest(request);
            }
            if (workQueue.empty()) { // recheck to see if queue is empty
                threadMutex.lock();
                done = true;
                threadMutex.unlock();
            }
        }
        
    }

    void processRequest(const std::pair<int, std::string> item) {
        int maxLoggingLevel = 3;
        Logger logger(3);
        TestExecutor testExecutor;
        TestResponse response;

        response = testExecutor.Execute(availableClassesToTest[item.second]);
        logger.Log(response);
        cout << "\n\t test run on: " << item.second << " is complete : sending results\n";
        
        auto myid = this_thread::get_id();
        stringstream ss;
        ss << myid;
        string serverThreadString = ss.str();

        JsonMessageGenerator jsonGenerator("Server Thread" + serverThreadString, sourceAddress, std::to_string(item.first));
        const char* messresp = jsonGenerator.GenerateMessageFromTestResponse(response);

        // Send a message to the connection
        send(item.first, messresp, (int)strlen(messresp), 0);
    }
};

int main() {
    
    const char *connect_ok = "message_rcvd_by_server";
    const char* welcomeMsg = "Test Harness Server Connected:\nPlease enter a command (--help for available commands):\n>";
    const char* cmd_help = "--help";
    const char* cmd_exit = "--exit";
    const char* cmd_classes = "--classes";
    const char* msg_help = "\nHELP:\n --help - displays help menu\n --classes - displays possible classes available for test\n --exit - close connection and quit\n>";
    const char* msg_sendtest = "\nTest Loaded...  testing in progress";
    const char* msg_exit = "\nserver connection closing...\n\n";
    const char* msg_badInput = "\nPlease enter a valid command. (--help for available commands)\n>";
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
    
    //grab the possible testable classes
	TestProfileLibrary library;
    tp.setAvailableClassesToTest(library.GetTestList());

    //create a JsonConverter to handle any JSON tasks
    JsonMessageGenerator jsonMessageGenerator("Server Main", result->ai_addr->sa_data, "stand-in destination addr");

    while (true) {
        char recvbuf[512] = { 0 }; // clear buffer
        std::string request = recvbuf;
        int recvbuflen = 512;
        int iResult, iSendResult;
        // Grab a connection from the queue
        cout << "\n\tSERVER:  Waiting for incoming connection...\n";
        ClientSocket = accept(ListenSocket, NULL, NULL);
        cout << " client connected - sending welcome message\n";

        //send welcome message
        iSendResult = send(ClientSocket, welcomeMsg, strlen(welcomeMsg), 0);
        if (iSendResult == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
        }

        //handler for client cmds
        do {
            recvbuf[0]='\0';// clear receive buffer
            cout << "receiving-";
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            cout << "received\n";
            if (iResult > 0) {
                //printf("Bytes received: %d\n", iResult);
                // Echo message received ok
                //iSendResult = send(ClientSocket, connect_ok, (int)strlen(connect_ok), 0);
                //printf("Bytes sent: %d\n", iSendResult);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    //return 1;
                }
            }
            else if (iResult == 0) {
                //printf("Connection closing...\n");
            }
            else {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                //return 1;
            }


            //CMD handling - help
            if (std::strcmp(recvbuf, cmd_help) == 0)
            {
                cout << " client cmd entered - help\n";

                const char* message = jsonMessageGenerator.GenerateMessage(msg_help, JsonMessageGenerator::MessageType::UIMessage);
                iSendResult = send(ClientSocket, message, strlen(message), 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
            }

            //CMD handling - classes
            else if (std::strcmp(recvbuf, cmd_classes) == 0)
            {
                cout << " client cmd entered - help\n";
                const char* possibleClasses = jsonMessageGenerator.GenerateMessageFromClassNames(tp.getAvailableClassesToTest());
                iSendResult = send(ClientSocket, possibleClasses, strlen(possibleClasses), 0);
                if (iSendResult == SOCKET_ERROR)
                {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
            }

            //CMD handling - exit
            else if (std::strcmp(recvbuf, cmd_exit) == 0)
            {
                cout << " client cmd entered - exit\n\n client disconnecting\n";
                const char* message = jsonMessageGenerator.GenerateMessage(msg_exit, JsonMessageGenerator::MessageType::Exit);
                iSendResult = send(ClientSocket, message, strlen(message), 0);
                if (iSendResult == SOCKET_ERROR)
                {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
                iResult = -1;
            }

            //CMD handling - a test was selected
            else if (tp.getAvailableClassesToTest().count(recvbuf) > 0)   // if it's a test request...send to queue
            {
                cout << " client cmd entered - " << recvbuf << "\n";
                const char* message = jsonMessageGenerator.GenerateMessage(msg_sendtest, JsonMessageGenerator::MessageType::UIMessage);
                iSendResult = send(ClientSocket, message, strlen(message), 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
                std::string request = recvbuf;
                tp.queueWork(ClientSocket, request);
                memset(recvbuf, 0, sizeof(recvbuf));
            }

            //An unrecognized command was provided
            else
            {
                cout << " client cmd entered - " << recvbuf << "\n";
                const char* message = jsonMessageGenerator.GenerateMessage(msg_badInput, JsonMessageGenerator::MessageType::UIMessage);
                iSendResult = send(ClientSocket, message, strlen(message), 0);                
                if (iSendResult == SOCKET_ERROR)
                {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
                memset(recvbuf, 0, sizeof(recvbuf));
            }

        } while (iResult > 0);
    }   
    closesocket(ListenSocket);
}