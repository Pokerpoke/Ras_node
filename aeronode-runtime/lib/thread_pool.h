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
#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <cstddef>
#include <queue>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace an
{
namespace core
{
class ThreadPool
{
  public:
    ThreadPool(size_t n_threads);
    ~ThreadPool();
    int push(std::function<void(void)> _task);
    size_t size() const;
    size_t tasks_remaining() const;
    size_t workers_remaining() const;

    ThreadPool &operator+=(std::function<void(void)> _task);

  private:
    size_t n_threads;
    std::vector<std::thread> workers;
    std::queue<std::function<void(void)>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
} // namespace core
} // namespace an
#endif //!_THREAD_POOL_H_