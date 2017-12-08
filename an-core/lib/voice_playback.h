/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    音频回放
 * @version  0.0.1
 * @example  qa_voice_playback.cc
 * @example  qa_voice_playback.cc
 * @example  voice-receive.cc
 * 
 * Last Modified:  2017-12-02
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#ifndef _VOICE_PLAYBACK_H_
#define _VOICE_PLAYBACK_H_

#include "voice_base.h"

namespace an
{
namespace core
{
/** 
 * @brief 音频回放类
 * 
 * 提供音频回放功能
 * 
 */
class VoicePlayback : public VoiceBase
{
  public:
	VoicePlayback(const std::string &dev);
	~VoicePlayback();

	int open_device();
	int playback(const char *input_buffer, const long input_buffer_size) const;

  private:
	int err;
};
}
}

#endif // !_VOICE_PLAYBACK_H_