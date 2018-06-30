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
#ifndef _TASK_H_
#define _TASK_H_

#include <functional>

namespace an
{
namespace core
{
class Task
{
  public:
    Task(std::function<void(void)> _task);
    ~Task();

    int run();
    bool terminate();
    int is_running();
    bool finished();

    Task &operator=(std::function<void(void)> _task);

  private:
};
} // namespace core
} // namespace an

#endif // !_TASK_H_