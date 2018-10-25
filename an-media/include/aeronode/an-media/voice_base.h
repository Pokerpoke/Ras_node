/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    音频采集、回放基类，设定相关参数
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-24
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#ifndef _VOICE_BASE_H_
#define _VOICE_BASE_H_

#include <string>
#include <alsa/asoundlib.h>

namespace an
{
namespace media
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
    VoiceBase(const std::string &device = "default");
    virtual ~VoiceBase();

    /// 码率
    int rate;
    /// 通道数
    int channels;
    /// 软件重采样
    int soft_resample;
    /// 每帧数据大小
    mutable int bits_per_frame;
    /// 默认输出缓存大小
    int default_output_buffer_size;
    /// 帧数
    snd_pcm_uframes_t frames;
    /// 缓存大小
    snd_pcm_uframes_t buffer_size;
    /// 缓存大小
    snd_pcm_uframes_t buffer_frames;
    /// 时间段大小
    snd_pcm_uframes_t period_size;
    /// 时间段大小
    snd_pcm_uframes_t period_frames;

    unsigned int period_time;
    unsigned int buffer_time;
    size_t bits_per_sample;

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
    // Flags
    bool DEVICE_OPENED;

    int set_params();
    int open_device();

  private:
    int err;
};
} // namespace media
} // namespace an

#endif // !_VOICE_BASE_H_