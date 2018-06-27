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
#include <chrono>
#include "aeronode/task.h"
#include "aeronode/task_queue.h"
#include "aeronode/thread_pool.h"
#include "aeronode/logger.h"
#include "aeronode/signaling.h"
#include <mutex>

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

    ThreadPool tp(4);

    Signaling s1;
    Signaling s2;
    s1.insert("test", "200");
    s2.insert("test", "200");
    mutex m;

    for (size_t i = 0; i < 10000; i++)
    {
        tp += [&] {
            unique_lock<mutex> lock(m);
            LOG(INFO) << stoi(s1.get("test")) + stoi(s2.get("test"));
            s1.set("test", to_string(stoi(s1.get("test")) + 1));
            s2.set("test", to_string(stoi(s2.get("test")) - 1));
            this_thread::sleep_for(chrono::microseconds(i));
        };
    }
    return 0;
}