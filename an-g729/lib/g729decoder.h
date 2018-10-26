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
 * Last Modified:  2018-10-26
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#ifndef _G729DECODER_H_
#define _G729DECODER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <bcg729/decoder.h>
#ifdef __cplusplus
}
#endif

namespace an
{
namespace g729
{
class G729Decoder
{
  public:
    G729Decoder();
    ~G729Decoder();

    int decoder(const char *input_buffer,
                const int input_buffer_size);

    char *output_buffer;
    int output_buffer_size;

  protected:
    bcg729DecoderChannelContextStruct *decoderChannelContext;

  private:
};
} // namespace g729
} // namespace an

#endif // !_G729DECODER_H_