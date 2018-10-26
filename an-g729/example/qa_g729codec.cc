/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-01
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-23
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include "aeronode/logger.h"
#include "aeronode/an-media/voice_capture.h"
#include "aeronode/an-media/voice_playback.h"
#include "aeronode/an-g729/g729encoder.h"
#include "aeronode/an-g729/g729decoder.h"

using namespace an::media;
using namespace an::g729;

int main()
{
    logger_init();

    G729Encoder e;
    G729Decoder d;
    VoiceCapture c("default");
    VoicePlayback p("default");

    while (1)
    {
        c.capture();
        e.encoder(c.output_buffer, c.output_buffer_size);
        d.decoder(e.output_buffer, e.output_buffer_size);
        p.playback(d.output_buffer, d.output_buffer_size);
    }

    getchar();
    return 0;
}