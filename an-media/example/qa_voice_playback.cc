/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    音频回放例程
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-24
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include <stdio.h>

#include "aeronode/logger.h"
#include "aeronode/an-media/voice_playback.h"

using namespace std;
using namespace an::media;

int main(int argc, char *argv[])
{
    logger_init();

    VoicePlayback p("default");

    FILE *pcm;
    if ((pcm = fopen("test.pcm", "r")) == NULL)
    {
        return 0;
    }

    int input_buffer_size = p.default_output_buffer_size;
    LOG(INFO) << p.default_output_buffer_size;
    char *input_buffer;

    int err;

    input_buffer = (char *)malloc(input_buffer_size);

    while ((err = fread(input_buffer,
                        sizeof(char),
                        input_buffer_size,
                        pcm)) > 0)
    {
        p.playback(input_buffer, input_buffer_size);
    }

    fclose(pcm);
    free(input_buffer);

    getchar();

    return 0;
}