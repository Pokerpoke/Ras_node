/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    音频捕获
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-23
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 * @example  qa_voice_capture_to_playback.cc
 * @example  qa_voice_capture.cc
 * @example  voice-send.cc
 * 
 */
#ifndef _VOICE_CAPTURE_H_
#define _VOICE_CAPTURE_H_

#include "voice_base.h"

namespace an
{
namespace media
{
/** 
 * @brief 音频捕获类
 * 
 * 提供了打开设备，捕获等功能
 * 
 */
class VoiceCapture : public VoiceBase
{
  public:
    /// 输出数据缓存
    char *output_buffer;
    /// 输出缓存大小
    unsigned int output_buffer_size;
    // int frames_to_read;
    /// 用于返回已读的帧数
    int frames_readed;

    VoiceCapture(const std::string &dev);
    ~VoiceCapture();

    friend std::ostream &operator<<(std::ostream &out, VoiceCapture &in);

    /** 
	 * @brief 打开设备
	 * 
	 * @retval	0	成功 
	 * @retval	-1	失败	  
	 * 
	 */
    int open_device();
    /** 
	 * @brief 音频捕获
	 * 
	 * 使用capture.output_buffer和capture.output_buffer_size来获取输出数据
	 * 
	 * @todo 返回类或者结构体
	 * 
	 */
    int capture();

  private:
    int err;
};
} // namespace media
} // namespace an

#endif // !_VOICE_CAPTURE_H_