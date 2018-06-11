/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-04
 * @date     2018-01
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-04-16
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#ifndef _G729ENCODER_H_
#define _G729ENCODER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <bcg729/encoder.h>
#ifdef __cplusplus
}
#endif

namespace an
{
namespace codec
{
class G729Encoder
{
  public:
    G729Encoder();
    ~G729Encoder();

    // @todo: try to encoder any length of input_buffer(maybe use another
    // buffer to recoder previous buffer is a solution)
    int encoder(const char *input_buffer,
                const int input_buffer_size);

    char *output_buffer;
    int output_buffer_size;

  protected:
    bcg729EncoderChannelContextStruct *encoderChannelContext;

  private:
    uint8_t t_output_buffer_size;
};
}
}

#endif // !_G729ENCODER_H_