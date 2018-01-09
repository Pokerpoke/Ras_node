/*******************************************************************************
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-01
 * @brief    G729编解码例程
 * @version  0.0.1
 * 
 * Last Modified:  2018-01-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 ******************************************************************************/
#include "logger.h"
#include "voice_capture.h"
#include "voice_playback.h"
#include "g729encoder.h"
#include "g729decoder.h"

using namespace an::core;
using namespace an::codec;

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