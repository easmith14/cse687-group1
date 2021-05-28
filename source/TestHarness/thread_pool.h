


#pragma once

//SOCKET headers
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <thread> // std::thread
#include <vector> // std::vector
#include <queue> // std::queue
#include <mutex> // std::mutex
#include <condition_variable> // std::condition_variable


class thread_pool {
public:
    thread_pool();

    ~thread_pool();

    void queueWork(int fd, std::string& request);

private:
    std::condition_variable_any workQueueConditionVariable;
    std::vector<std::thread> threads;
    std::mutex workQueueMutex;
    std::queue<std::pair<int, std::string>> workQueue;
    bool done;
    void doWork();
    void processRequest(const std::pair<int, std::string> item);
};