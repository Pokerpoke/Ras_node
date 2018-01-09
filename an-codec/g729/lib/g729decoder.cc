/*******************************************************************************
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-01
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-01-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 ******************************************************************************/
#include <stdlib.h>

#include "logger.h"
#include "g729decoder.h"

namespace an
{
namespace codec
{
G729Decoder::G729Decoder()
{
    decoderChannelContext = initBcg729DecoderChannel();
}
int G729Decoder::decoder(const char *input_buffer,
                         const int input_buffer_size)
{
    if (input_buffer_size % 10 != 0)
    {
        LOG(ERROR) << "The decoder can only decode length of multiples of 10.";
        return -1;
    }

    int multiples = input_buffer_size / 10;
    output_buffer_size = multiples * 160;
    output_buffer = (char *)malloc(output_buffer_size);

    for (int i = 0; i < multiples; i++)
    {
        bcg729Decoder(decoderChannelContext,
                      (uint8_t *)(input_buffer + i * 10),
                      10, 0, 0, 0,
                      (int16_t *)(output_buffer + i * 160));
    }
    return output_buffer_size;
}
G729Decoder::~G729Decoder()
{
    closeBcg729DecoderChannel(decoderChannelContext);
    free(output_buffer);
}
}
}