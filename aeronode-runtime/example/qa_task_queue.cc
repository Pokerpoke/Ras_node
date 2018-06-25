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
#include "aeronode/task.h"
#include "aeronode/task_queue.h"
#include "aeronode/thread_pool.h"
#include "aeronode/logger.h"

#include "aeronode/voice_capture.h"
#include "aeronode/voice_playback.h"
#include "aeronode/rtp_sender.h"
#include "aeronode/rtp_receiver.h"
#include "aeronode/an-g729/g729encoder.h"
#include "aeronode/an-g729/g729decoder.h"

using namespace std;
using namespace an::core;
using namespace an::codec;

void hello()
{
    LOG(INFO) << "hello";
}

int main(int argc, char const *argv[])
{
    logger_init();

    ThreadPool tp(10);

    for (size_t i = 0; i < 10; i++)
    {
        tp.push([i] {
            LOG(INFO) << "hello" << i;
        });
    }
    tp += hello;

    TaskQueue tq;
    Task t(
        []() -> void {
            LOG(INFO) << "hello";
        });
    tq.add_task();
    tq += t;

    getchar();
    return 0;
}