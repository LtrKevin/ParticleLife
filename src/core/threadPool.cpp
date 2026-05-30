#include "threadPool.h"

ThreadPool::ThreadPool(int numThreads) {
    for (int i = 0; i < numThreads; i++) {
        threads_.emplace_back([this] {
            while (true) {
                std::unique_lock lock(mutex_);
                cv_.wait(lock, [this] { return !tasks_.empty() || stop_;});

                if (stop_) break;

                auto task = tasks_.front();
                tasks_.pop();
                lock.unlock();

                task();

                lock.lock();
                --activeTasks_;
                lock.unlock();

                cvDone_.notify_all();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock lock(mutex_);
        stop_ = true;
    }
    cv_.notify_all();
    for (auto& thread : threads_) thread.join();
}

void ThreadPool::submit(std::function<void()> task) {
    {
        std::unique_lock lock(mutex_);
        tasks_.push(task);
        ++activeTasks_;
    }
    cv_.notify_all();
}

void ThreadPool::wait() {
    std::unique_lock lock(mutex_);
    cvDone_.wait(lock, [this] {return activeTasks_ == 0;});
}
