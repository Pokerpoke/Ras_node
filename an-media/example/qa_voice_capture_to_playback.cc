/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    音频捕获并回放例程
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-24
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include "aeronode/an-media/voice_playback.h"
#include "aeronode/an-media/voice_capture.h"
#include "aeronode/an-media/bandpass_filter.h"
#include "aeronode/logger.h"

using namespace std;
using namespace an::media;

int main()
{
    logger_init();

    VoicePlayback p("default");
    VoiceCapture c("default");

    while (1)
    {
        c.capture();
        // f.filter(c.output_buffer, c.frames_readed);
        p.playback(c.output_buffer, c.output_buffer_size);
    }

    return 0;
}