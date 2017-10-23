/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file      
 * @author    姜阳
 * @date      2017.10
 * @brief     音频采集、回放基类，设定相关参数
 * @version   0.0.1
 * 
 */
#ifndef _VOICE_BASE_H_
#define _VOICE_BASE_H_

#include <string>
#include <alsa/asoundlib.h>

namespace an
{
namespace core
{
/** 
 * @brief 音频捕获、回放基类
 * 
 * 包含了音频捕获、回放所共有的一些参数，以及硬件参数设置，继承该类需要实现open_device()
 * 
 */
class VoiceBase
{
public:
  VoiceBase(const std::string &device);
  virtual ~VoiceBase();

  /// 码率
  unsigned int rate;
  /// 通道数
  unsigned int channels;
  /// 软件重采样
  unsigned int soft_resample;
  /// 每帧数据大小
  unsigned int bytes_per_frame;
  /// 默认缓存大小
  unsigned int default_buffer_size;
  /// 默认时间段大小
  unsigned int default_period_size;
  /// 帧数
  snd_pcm_uframes_t frames;
  /// 缓存大小
  snd_pcm_uframes_t buffer_size;
  /// 时间段大小
  snd_pcm_uframes_t period_size;

protected:
  /// 设备名称
  const char *device;

  /// 设备句柄
  snd_pcm_t *handle;
  /// 硬件参数结构体
  snd_pcm_hw_params_t *params;
  /// 采样格式
  snd_pcm_format_t format;
  /// 访问方式
  snd_pcm_access_t access_type;

  // Flags
  bool PARAMS_SETED;
  bool DEVICE_OPENED;

  int set_params();
  virtual int open_device() = 0;

private:
  int err;
};
}
}

#endif // !_VOICE_BASE_H_