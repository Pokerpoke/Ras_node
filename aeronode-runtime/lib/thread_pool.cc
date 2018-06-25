/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-06
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-06-25
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "thread_pool.h"
#include <future>

namespace an
{
namespace core
{
ThreadPool::ThreadPool(size_t n_threads)
    : n_threads(n_threads < 1 ? 1 : n_threads),
      stop(false)
{
    for (size_t i = 0; i < n_threads; i++)
    {
        workers.emplace_back(
            [this] {
                while (1)
                {
                    std::function<void(void)> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }
}

int ThreadPool::push(std::function<void(void)> _task)
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    tasks.emplace(_task);
    condition.notify_one();
    return 0;
}

size_t ThreadPool::size() const
{
    return n_threads;
}

ThreadPool &ThreadPool::operator+=(std::function<void(void)> _task)
{
    this->push(_task);
    return *this;
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::vector<std::thread>::iterator worker = workers.begin();
         worker != workers.end();
         worker++)
    {
        (*worker).join();
    }
}
} // namespace core
} // namespace an