/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-23
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include <fstream>

#include "aeronode/an-media/voice_capture.h"
#include "aeronode/logger.h"

using namespace std;
using namespace an::media;

int main()
{
    logger_init();

    VoiceCapture c("default");

    ofstream output("test.pcm", ios::trunc | ios::binary);

    int loop_sec;
    loop_sec = 10;
    unsigned long loop_limit;
    loop_limit = loop_sec * c.rate;

    for (size_t i = 0; i < loop_limit; i++)
    {
        output << c;
        i += c.frames_readed;
    }

    output.close();

    return 0;
}