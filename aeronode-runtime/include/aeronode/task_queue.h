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
#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include "task.h"

namespace an
{
namespace core
{
class TaskQueue
{
  public:
    TaskQueue();
    ~TaskQueue();

    int add_task();
    int get_num();
    bool clear();

    TaskQueue &operator+=(const an::core::Task &_task);

  private:
};
} // namespace core
} // namespace an

#endif // !_TASK_QUEUE_H_