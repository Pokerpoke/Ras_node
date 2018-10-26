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
 * Last Modified:  2018-10-26
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include "aeronode/logger.h"
#include "aeronode/an-media/voice_base.h"

namespace an
{
namespace media
{
/** 
 * @brief 音频捕获、回放构造函数
 * 
 * @param[in]	dev	设备名称，可以传入default来使用默认设备
 * 
 */
VoiceBase::VoiceBase(const std::string &dev)
{
    device = dev.c_str();
    channels = 2;
    rate = 8000;
    soft_resample = 1;
    format = SND_PCM_FORMAT_S16_LE;
    access_type = SND_PCM_ACCESS_RW_INTERLEAVED;
    // 16 bits per sample
    // 32 bits = 4 Bytes per frame
    // frames * 4 < MTU = 1500 (most networks) -> frames = 256
    frames = 480;

    DEVICE_OPENED = false;
    PARAMS_SETED = false;

    bits_per_sample = snd_pcm_format_physical_width(format);
    bits_per_frame = bits_per_sample * channels;
    default_output_buffer_size = frames * bits_per_frame / 8; // in byte

    buffer_frames = frames * 8;
    period_frames = buffer_frames / 4;
    period_time = 0;
    buffer_time = 0;
}

/** 
 * @brief 音频捕获、回放基类析构函数
 * 
 */
VoiceBase::~VoiceBase()
{
    if (DEVICE_OPENED)
    {
        if ((err = snd_pcm_close(handle)) < 0)
        {
            LOG(ERROR) << "Close device error.";
        }
        else
        {
            LOG(INFO) << "Device has been closed.";
        }
    }
}

/** 
 * @brief 设置硬件参数
 * 
 * 设置相关的硬件参数
 * 
 * @retval	0	成功
 * @retval	-1	失败
 * 
 */
int VoiceBase::set_params()
{
    if (!DEVICE_OPENED)
        return -1;

    // 分配硬件参数空间
    snd_pcm_hw_params_alloca(&params);

    // 以默认值填充硬件参数
    if ((err = snd_pcm_hw_params_any(handle, params)) < 0)
    {
        LOG(ERROR) << "Initialize parameters error for : "
                   << snd_strerror(err);
        return -1;
    }
    else
    {
        LOG(INFO) << "Initialize parameters success.";
    }

    if ((err = snd_pcm_hw_params_set_rate_resample(handle,
                                                   params,
                                                   soft_resample)) < 0)
    {
        LOG(ERROR) << "Set resample error for : "
                   << snd_strerror(err);
        return -1;
    }
    else
    {
        LOG(INFO) << "Set resample success.";
    }

    // 设置访问方式，默认为交错读写，可以设置为内存映射等
    if ((err = snd_pcm_hw_params_set_access(handle,
                                            params,
                                            access_type)) < 0)
    {
        LOG(ERROR) << "Set access type error for : "
                   << snd_strerror(err);
        return -1;
    }
    else
    {
        LOG(INFO) << "Set access type success.";
    }

    // 设置格式，S16_LE等
    if ((err = snd_pcm_hw_params_set_format(handle,
                                            params,
                                            format)) < 0)
    {
        LOG(ERROR) << "Set format error for : "
                   << snd_strerror(err);
        return -1;
    }
    else
    {
        LOG(INFO) << "Set format success.";
    }

    // 设置通道数，1或2
    if ((err = snd_pcm_hw_params_set_channels(handle,
                                              params,
                                              channels)) < 0)
    {
        LOG(ERROR) << "Set channels error for : "
                   << snd_strerror(err);
        return -1;
    }
    else
    {
        LOG(INFO) << "Set channels to " << channels << " success.";
    }

    // 设置码率，会取一个与设定值相近的码率
    unsigned int rrate;
    rrate = rate;
    if ((err = snd_pcm_hw_params_set_rate_near(handle,
                                               params,
                                               &rrate,
                                               0)) < 0)
    {
        LOG(ERROR) << "Set rate error for : "
                   << snd_strerror(err);
        return -1;
    }
    else
    {
        if (rrate == rate)
            LOG(INFO) << "Set rate to " << rrate << "Hz success.";
        else
            LOG(WARN) << "Rate " << rate
                      << "Hz not available, get " << rrate << "Hz.";
    }

    if (buffer_time == 0 && buffer_frames == 0)
    {
        err = snd_pcm_hw_params_get_buffer_time_max(params,
                                                    &buffer_time,
                                                    0);
        assert(err >= 0);
        if (buffer_time > 500000)
            buffer_time = 500000;
    }
    if (period_time == 0 && period_frames == 0)
    {
        if (buffer_time > 0)
            period_time = buffer_time / 4;
        else
            period_frames = buffer_frames / 4;
    }
    if (period_time > 0)
        err = snd_pcm_hw_params_set_period_time_near(handle,
                                                     params,
                                                     &period_time,
                                                     0);
    else
        err = snd_pcm_hw_params_set_period_size_near(handle,
                                                     params,
                                                     &period_frames,
                                                     0);
    assert(err >= 0);
    if (buffer_time > 0)
    {
        err = snd_pcm_hw_params_set_buffer_time_near(handle, params,
                                                     &buffer_time,
                                                     0);
    }
    else
    {
        err = snd_pcm_hw_params_set_buffer_size_near(handle, params,
                                                     &buffer_frames);
    }
    assert(err >= 0);
    // // 设置缓存大小，以Byte为单位的计算公式为：frames * bits_per_frame
    // // 以frames为单位
    // if ((err = snd_pcm_hw_params_set_buffer_size_near(handle,
    //                                                   params,
    //                                                   &buffer_frames)) < 0)
    // {
    //     LOG(ERROR) << "Set buffer size error.";
    //     return -1;
    // }
    // else
    // {
    //     snd_pcm_uframes_t t_buffer_frames;
    //     snd_pcm_hw_params_get_buffer_size(params, &t_buffer_frames);
    //     if (t_buffer_frames != buffer_frames)
    //     {
    //         LOG(WARN) << "Buffer size " << buffer_frames
    //                   << " not available, get " << t_buffer_frames << " frames.";
    //     }
    //     else
    //     {
    //         LOG(INFO) << "Buffer size set to " << buffer_frames << " frames.";
    //     }
    // }

    // // 设置段大小，一般为buffer_size或buffer_frames的1 / 2或者1 / 4；
    // if ((err = snd_pcm_hw_params_set_period_size_near(handle, params, &period_frames, 0)) < 0)
    // {
    //     LOG(ERROR) << "Set period size error for : " << snd_strerror(err);
    //     return -1;
    // }
    // else
    // {
    //     snd_pcm_uframes_t t_period_frames;
    //     snd_pcm_hw_params_get_period_size(params, &t_period_frames, 0);
    //     if (t_period_frames != period_frames)
    //     {
    //         LOG(WARN) << "Period size " << period_frames
    //                   << " not available, get " << t_period_frames << " frames.";
    //     }
    //     else
    //     {
    //         LOG(INFO) << "Period size set to " << period_frames << " frames.";
    //     }
    // }

    // 将参数写入设备
    if ((err = snd_pcm_hw_params(handle, params)) < 0)
    {
        LOG(ERROR) << "Set parameters error for : "
                   << snd_strerror(err);
        return -1;
    }
    else
    {
        LOG(INFO) << "Set parameters success.";
        PARAMS_SETED = true;
    }
    snd_pcm_uframes_t t_buffer_frames;
    snd_pcm_hw_params_get_buffer_size(params, &t_buffer_frames);
    buffer_frames = t_buffer_frames;
    LOG(INFO) << "Buffer size seted to " << t_buffer_frames << " frames.";
    snd_pcm_uframes_t t_period_frames;
    snd_pcm_hw_params_get_period_size(params, &t_period_frames, 0);
    period_frames = t_period_frames;
    LOG(INFO) << "Period size seted to " << t_period_frames << " frames.";
    return 0;
}

void VoiceBase::set_silence(char *data, int size)
{
    int err = snd_pcm_format_set_silence(format,
                                         data,
                                         size * 8 / bits_per_frame);
    if (err < 0)
        LOG(ERROR) << "Set silence failed.";
}
} // namespace media
} // namespace an