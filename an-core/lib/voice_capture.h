/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file      
 * @author    姜阳
 * @date      2017.10
 * @brief     音频捕获
 * @version   1.0.0
 * @example   qa_voice_capture.cc
 * 
 */
#ifndef _VOICE_CAPTURE_H_
#define _VOICE_CAPTURE_H_

#include "voice_base.h"

namespace an
{
namespace core
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

	int open_device();
	int capture();

  private:
	int err;
};
}
}

#endif // !_VOICE_CAPTURE_H_