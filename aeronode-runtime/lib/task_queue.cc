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
#include "logger.h"
#include "task_queue.h"
namespace an
{
namespace core
{
TaskQueue::TaskQueue()
{
}

int TaskQueue::add_task()
{
    return 0;
}

TaskQueue &TaskQueue::operator+=(const an::core::Task &_task)
{
    return *this;
}

TaskQueue::~TaskQueue()
{
}
} // namespace core
} // namespace an