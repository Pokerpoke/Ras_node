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
 * Last Modified:  2018-04-24
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <stdlib.h>

#include "aeronode/logger.h"
#include "g729encoder.h"

namespace an
{
namespace codec
{
G729Encoder::G729Encoder()
{
    // encoderChannelContext = new bcg729EncoderChannelContextStruct;
    encoderChannelContext = initBcg729EncoderChannel(0);

    output_buffer_size = 10;
    output_buffer = (char *)malloc(output_buffer_size);
}

int G729Encoder::encoder(const char *input_buffer,
                         const int input_buffer_size)
{
    if (input_buffer_size % 160 != 0)
    {
        LOG(ERROR) << "The encoder can only encode lenght of multiples of 160.";
        return -1;
    }

    int multiples = input_buffer_size / 160;
    output_buffer_size = multiples * 10;
    output_buffer = (char *)malloc(output_buffer_size);

    for (int i = 0; i < multiples; i++)
    {
        bcg729Encoder(encoderChannelContext,
                      (int16_t *)(input_buffer + i * 160),
                      (uint8_t *)(output_buffer + i * 10),
                      (uint8_t *)&t_output_buffer_size);
        if ((int)t_output_buffer_size != 10)
        {
            LOG(ERROR) << "Something wrong with bcg729encoder.";
            return -1;
        }
    }

    return output_buffer_size;
}

G729Encoder::~G729Encoder()
{
    closeBcg729EncoderChannel(encoderChannelContext);
    free(output_buffer);
}
}
}