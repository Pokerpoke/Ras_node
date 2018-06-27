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
 * Last Modified:  2018-06-26
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aeronode/thread_pool.h"
#include "gtest/gtest.h"
#include <mutex>

namespace
{
TEST(ThreadPoolTest, ThreadPoolTest_First_Test)
{
    using namespace an::core;
    class test
    {
      public:
        test(int a, int b)
        {
            this->a = a;
            this->b = b;
        };
        ~test(){};
        int add()
        {
            a = a - 1;
            b = b + 1;
            return a + b;
        }

      private:
        int a;
        int b;
    };
    ThreadPool tp(4);
    test t(100, 200);
    std::mutex m;
    for (size_t i = 0; i < 10000; i++)
    {
        tp += [&t, &m] {
            std::unique_lock<std::mutex> lock(m);
            EXPECT_EQ(300, t.add());
        };
    }
}
} // namespace