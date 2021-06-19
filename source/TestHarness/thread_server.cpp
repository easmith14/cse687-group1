// 
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
#include <string>
#include "TestResponse.h"

#pragma warning(disable : 4996)

using namespace std;
#define DEFAULT_PORT "13379"
const int recvbuflen = 2048;
const char* connect_ok = "message_ok";

typedef void(__cdecl* f_char_ptr)(std::string, int);
typedef int(__cdecl * f_vehicle_ptr)(std::string, int, int, int, int);
typedef TestResponse(__cdecl * f_test_ptr)();
const static bool dllDir = SetDllDirectory(TEXT("..\\DLLs"));

// This class manages a thread pool that will process requests
class thread_pool {
public:
    thread_pool(Logger* a) 
        : logger(a), done(false), results_count(0) {
        // This returns the number of threads supported by the system. If the
        // function can't figure out this information, it returns 0. 0 is not good,
        // so we create at least 1
        //auto numberOfThreads = std::thread::hardware_concurrency();
        int numberOfThreads = 4;
        cout << numberOfThreads << "-test threads have been started\n";
        if (numberOfThreads == 0) {
            numberOfThreads = 1;
        }

        for (unsigned i = 0; i < numberOfThreads; ++i) {
            // The threads will execute the private member `doWork`. Note that we need
            // to pass a reference to the function (namespaced with the class name) as
            // the first argument, and the current object as second argument
            threads.push_back(std::thread(&thread_pool::doWork, this));
            threads[i].detach();
        }
    }

    // The destructor joins all the threads so the program can exit gracefully.
    // This will be executed if there is any exception (e.g. creating the threads)
    ~thread_pool() {
        // So threads know it's time to shut down
        done = true;
        cout << "\t\n shutting down threads....\n";
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
        std::lock_guard<std::mutex> g(workQueueMutex);

        workQueue.push(std::pair<int, std::string>(fd, request));

        // Notify one thread that there are requests to process
        done = false;
        workQueueConditionVariable.notify_one();
    }

    void setDone(bool done)
    {
        done = done;
    }

    int getResultsCount()
    {
        return results_count;
    }

    void queueWorkResults() { // once initiated will send results to client
        cout << "\n  thread id = " << std::this_thread::get_id() << " sending results\n";

        while(!sendQueue.empty())
        {
            std::pair<int, std::string> request;
            {
                request = sendQueue.front();
                sendQueue.pop();
            }

            const char* c = request.second.c_str();
            char recvbuf2[recvbuflen] = { 0 };

            int iResult = send(request.first, c, (int)strlen(c), 0);
            if (iResult > 1) {
                // get ack here
                int sendResult = recv(request.first, recvbuf2, recvbuflen, 0);
                if (std::strcmp(recvbuf2, connect_ok) == 0) {
                    cout << "thread id: " << std::this_thread::get_id() << " send successful\n";
                }
                else {
                    printf("client did not ack result: %d\n", sendResult);
                    WSACleanup();
                }
            }
            else {
                printf("send failed: %d\n", iResult);
                WSACleanup();
            }
        }
    }




private:
    // This condition variable is used for the threads to wait until there is work
    // to do
    std::condition_variable_any workQueueConditionVariable;
    std::condition_variable_any sendQueueConditionVariable;

    // We store the threads in a vector, so we can later stop them gracefully
    std::vector<std::thread> threads;

    // Mutex to protect workQueue
    std::mutex workQueueMutex;
    std::mutex threadMutex;
    std::mutex sendQueueMutex;

    // Queue of requests waiting to be processed
    std::queue<std::pair<int, std::string>> workQueue;

    std::queue<std::pair<int, std::string>> sendQueue;

    //address that we are running from (for message purposes)
    std::string sourceAddress;

    // This will be set to true when the thread pool is shutting down. This tells
    // the threads to stop looping and finish
    bool done;

    // Store a pointer to the logger created in main 
    Logger* logger;

    int results_count;

    // Function used by the threads to grab work from the queue
    void doWork() {
        // Loop while the queue is not destructing
        while (!done) {
            cout << "\n  thread id = " << std::this_thread::get_id() << " is waiting for work \n";
            std::pair<int, std::string> request;
            {
                std::unique_lock<std::mutex> lck(workQueueMutex);
                workQueueConditionVariable.wait(lck, [&] {return !workQueue.empty() || done; });
                cout << "\n thread id = " << std::this_thread::get_id() << " is awake \n";
                // Only wake up if there are elements in the queue or the program is shutting down
                request = workQueue.front();
                workQueue.pop();
                cout << "\n  thread id = " << std::this_thread::get_id() << " is working on " << request.second << "\n";
            }
            processRequest(request);
        }
    }

    void processRequest(const std::pair<int, std::string> item) {
        
        TestExecutor *testExecutor=new TestExecutor;
        TestResponse response;

        //  WORK IN PROGRESS //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string dllToTest = item.second;
        char* cstr = new char[dllToTest.length() + 1];
        std::strcpy(cstr, dllToTest.c_str());
        HMODULE hGetMod = LoadLibraryA(cstr);

        // lol a lot of this is hard coded for now because I didn't think well enough ahead
        if (dllToTest == "Character.dll")
        {
            f_char_ptr create_character_ptr = (f_char_ptr)GetProcAddress(hGetMod, "create_character");
            cout << "\nPreparing to load DLL function...\n";
            create_character_ptr("Sigmar", 500);
            if (!create_character_ptr)
            {
                cout << "Failed to load function!!\n\n";
            }
            else
            {
                cout << "Function loaded!!\n\n";
            }
        }
        else if (dllToTest == "Vehicle.dll")
        {
            f_vehicle_ptr create_vehicle_ptr = (f_vehicle_ptr)GetProcAddress(hGetMod, "create_vehicle");
            create_vehicle_ptr("Cybertruck", 30, 19, 4, 7);
            if (!create_vehicle_ptr)
            {
                cout << "Failed to load function!!\n\n";
            }
            else
            {
                cout << "Function loaded!!\n\n";
            }
        }
        else
        {
            // Something probably went bad and didn't work so here is a random character
            f_char_ptr create_character_ptr = (f_char_ptr)GetProcAddress(hGetMod, "create_character");
            create_character_ptr("Grombrindal", 100);
            if (!create_character_ptr)
            {
                cout << "Failed to load function!!\n\n";
            }
            else
            {
                cout << "Function loaded!!\n\n";
            }
        }

        // temporarily circumventing test executor until it can be refactored
        f_test_ptr test_ptr = (f_test_ptr)GetProcAddress(hGetMod, "test");
        response = test_ptr();
        response.ClassName = item.second; // added to record dll in response

        //TestResponse dllTestResponse = test_ptr();
        logger->Log(response);

        FreeLibrary(hGetMod);
        cout << "\n\t DLL test run on: " << item.second << " is complete : sending results\n";
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        auto myid = this_thread::get_id();
        stringstream ss;
        ss << myid;
        string serverThreadString = ss.str();

        JsonMessageGenerator jsonGenerator("Server Thread" + serverThreadString, sourceAddress, std::to_string(item.first));
        string messresp = jsonGenerator.GenerateMessageFromTestResponse(response);
        threadMutex.lock();
        sendQueue.push(std::pair<int, std::string>(item.first, messresp));
        results_count++;
        threadMutex.unlock();
        cout << myid << " thread is complete\n";
    }
};

int main() {
    
    const char *connect_ok = "message_rcvd_by_server";
    const char* welcomeMsg = "Test Harness Server Connected:\nPlease select one or many classes to test, separated by spaces\n(or --help for available commands):\n";
    const char* cmd_help = "--help";
    const char* cmd_exit = "--exit";
    const char* cmd_done = "--done";
    const char* cmd_classes = "--classes";
    const char* msg_help = "\nHELP:\n --help - displays help menu\n --classes - displays possible classes available for test\n --exit - close connection and quit\n>";
    const char* msg_sendtest = "\nTest Loaded...  testing in progress\n";
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

    // create logger object for the threadpool
    int logLevel = 3;
    Logger logger(logLevel);

    // start the threadpool
    thread_pool tp(&logger);


    //grab the possible testable classes
	TestProfileLibrary library;
    vector<string> availableClassesToTest = library.GetTestList();


    //create a JsonConverter to handle any JSON tasks
    JsonMessageGenerator jsonMessageGenerator("Server Main", result->ai_addr->sa_data, "stand-in destination addr");

    //while (true) {

        
        char recvbuf[recvbuflen] = { 0 }; // clear buffer
        std::string request = recvbuf;

        int iSendResult;
        // Grab a connection from the queue
        cout << "\n\tSERVER:  Waiting for incoming connection...\n";
        ClientSocket = accept(ListenSocket, NULL, NULL);
        cout << " client connected - sending welcome message\n";

        //send welcome message and initial classes list to prep user
        
        const char* message = jsonMessageGenerator.GenerateMessage(welcomeMsg, JsonMessageGenerator::MessageType::UIMessage);
        iSendResult = send(ClientSocket, message, (int)strlen(message), 0);
        if (iSendResult == SOCKET_ERROR)
        {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
        }
        message = jsonMessageGenerator.GenerateMessageFromClassNames(availableClassesToTest);
        iSendResult = send(ClientSocket, message, (int)strlen(message), 0);
        if (iSendResult == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
        }

        int testcount = 0;
        //memset(recvbuf, 0, sizeof(recvbuf));
        //handler for client cmds
        do {
            recvbuf[0]='\0';// clear receive buffer
            cout << "receiving-";
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if (iResult == 0) {
                printf("Connection closing...\n");
            }
            else if (iResult < 0) {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
            }
            if (iResult>0)
                {
                request = recvbuf;
                cout << "received\n";
            //parse recieved string into JSON
                Json::Value json = jsonMessageGenerator.GetValueFromJsonString(recvbuf);
                const char* recievedBody = _strdup(json["Body"].asString().c_str());

            //check to see if it is a command
                if (json["MessageType"].asInt() == JsonMessageGenerator::MessageType::ClassSelection)
                    {
                    cout << " client requested test for class - " << recievedBody << "\n";
                    const char* message = jsonMessageGenerator.GenerateMessage(msg_sendtest, JsonMessageGenerator::MessageType::UIMessage);
                    iSendResult = send(ClientSocket, message, (int)strlen(message), 0);
                        if (iSendResult == SOCKET_ERROR) {
                            printf("send failed: %d\n", WSAGetLastError());
                            closesocket(ClientSocket);
                        WSACleanup();
                        }
                    string request = recievedBody;
                    tp.queueWork(ClientSocket, request);
                    testcount++;
                    }
                //CMD handling - help
                else if (std::strcmp(recievedBody, cmd_help) == 0)
                    {
                    cout << " client cmd entered - help\n";
                    const char* message = jsonMessageGenerator.GenerateMessage(msg_help, JsonMessageGenerator::MessageType::UIMessage);
                    iSendResult = send(ClientSocket, message, (int)strlen(message), 0);
                    if (iSendResult == SOCKET_ERROR) {
                        printf("send failed: %d\n", WSAGetLastError());
                        closesocket(ClientSocket);
                        WSACleanup();
                        }
                    }
                //CMD handling - classes
                else if (std::strcmp(recievedBody, cmd_classes) == 0)
                    {
                        cout << " client cmd entered - classes\n";
                        const char* possibleClasses = jsonMessageGenerator.GenerateMessageFromClassNames(availableClassesToTest);
                        iSendResult = send(ClientSocket, possibleClasses, (int)strlen(possibleClasses), 0);
                        if (iSendResult == SOCKET_ERROR) {
                        printf("send failed: %d\n", WSAGetLastError());
                        closesocket(ClientSocket);
                        WSACleanup();
                        }
                    }
                //CMD handling - exit
                    else if (std::strcmp(recievedBody, cmd_exit) == 0)
                    {
                        cout << " client cmd entered - exit\n\n client disconnecting\n";
                        const char* message = jsonMessageGenerator.GenerateMessage(msg_exit, JsonMessageGenerator::MessageType::Exit);
                        iSendResult = send(ClientSocket, message, (int)strlen(message), 0);
                        if (iSendResult == SOCKET_ERROR) {
                            printf("send failed: %d\n", WSAGetLastError());
                            closesocket(ClientSocket);
                            WSACleanup();
                        }
                    iResult = -1;
                    }
                    else if (std::strcmp(recievedBody, cmd_done) == 0) // added to coordinate when tests are complete
                    {
                    cout << "client finshed sending test requests\n";
                    iResult = 0;
                    }
                //An unrecognized command was provided
                else
                    {
                        cout << " client cmd entered - " << recievedBody << "\n";
                        const char* message = jsonMessageGenerator.GenerateMessage(msg_badInput, JsonMessageGenerator::MessageType::UIMessage);
                        iSendResult = send(ClientSocket, message, (int)strlen(message), 0);                
                        if (iSendResult == SOCKET_ERROR) {
                        printf("send failed: %d\n", WSAGetLastError());
                        closesocket(ClientSocket);
                        WSACleanup();
                        }
                    }
                }
            } while (iResult > 0);

            //wait for results to be complete before sending
            int results_count = tp.getResultsCount();
            while (results_count != testcount) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                results_count = tp.getResultsCount();
            }
            tp.queueWorkResults();
            //tp.~thread_pool();

            closesocket(ClientSocket);
         ////

    //}   
    

    system("PAUSE");
    closesocket(ListenSocket);
    exit(1);
}