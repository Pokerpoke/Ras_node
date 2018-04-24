/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    rtp接收，回调函数方式例程
 * @version  0.0.1
 * 
 * Last Modified:  2018-04-24
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <stdio.h>
#include <sched.h>
#include <iostream>

#include "aeronode/rtp_receiver.h"
#include "aeronode/voice_playback.h"
#include "aeronode/logger.h"

using namespace std;
using namespace an::core;

int main()
{
    logger_init();

    RTPReceiver r(13374);
    VoicePlayback p("default");

    r.start_listen([&] {
        p.playback(r.output_buffer, r.output_buffer_size);
    });

    return 0;
}