#pragma once

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>

class ThreadPool {
public:
    ThreadPool(int numThreads);
    ~ThreadPool();
    void submit(std::function<void()> task);
    void wait();

private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::condition_variable cvDone_;
    std::atomic<int> activeTasks_{0};
    bool stop_ = false;
};
