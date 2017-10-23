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
#include "logger.h"
#include "voice_base.h"

namespace an
{
namespace core
{
/** 
 * @brief 音频捕获、回放构造函数
 * 
 * @param	dev	设备名称，可以传入default来使用默认设备
 * 
 */
VoiceBase::VoiceBase(const std::string &dev)
{
	device = dev.c_str();
	channels = 2;
	rate = 44100;
	// rate = 8000;
	frames = 32;
	soft_resample = 1;
	format = SND_PCM_FORMAT_S16_LE;
	access_type = SND_PCM_ACCESS_RW_INTERLEAVED;

	DEVICE_OPENED = false;
	PARAMS_SETED = false;

	bytes_per_frame = snd_pcm_format_width(format) / 8 * channels;

	default_buffer_size = frames * bytes_per_frame;
	default_period_size = default_buffer_size / 2;

	buffer_size = static_cast<snd_pcm_uframes_t>(default_buffer_size);
	period_size = static_cast<snd_pcm_uframes_t>(default_period_size);
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
			LOG(ERROR) << "Close Device error.";
		}
		else
		{
			LOG(INFO) << "Close Device success.";
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
		LOG(ERROR) << "Initialize parameters error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Initialize parameters success.";
	}

	// 设置访问方式，默认为交错读写，可以设置为内存映射等
	if ((err = snd_pcm_hw_params_set_access(handle,
											params,
											access_type)) < 0)
	{
		LOG(ERROR) << "Set access type error.";
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
		LOG(ERROR) << "Set format error.";
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
		LOG(ERROR) << "Set channels error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set channels success.";
	}

	// 设置码率，会取一个与设定值相近的码率
	unsigned int rrate;
	rrate = rate;
	if ((err = snd_pcm_hw_params_set_rate_near(handle,
											   params,
											   &rrate, 0)) < 0)
	{
		LOG(ERROR) << "Set rate error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set rate to " << rrate << "Hz success.";
		if (rrate != rate)
		{
			LOG(WARN) << "Rate " << rate << "Hz not available, get " << rrate << "Hz.";
		}
	}

	// 设置缓存大小，计算公式为：frames * bytes_per_frame
	if ((err = snd_pcm_hw_params_set_buffer_size_near(handle,
													  params,
													  &buffer_size)) < 0)
	{
		LOG(ERROR) << "Set buffer size error.";
		return -1;
	}
	else
	{
		snd_pcm_uframes_t t_buffer_size;
		snd_pcm_hw_params_get_buffer_size(params, &t_buffer_size);
		if (t_buffer_size != buffer_size)
		{
			LOG(WARN) << "Buffer size " << buffer_size
					  << " not available, get " << t_buffer_size << " frames.";
		}
		else
		{
			LOG(INFO) << "Buffer size set to " << buffer_size << " frames.";
		}
	}

	// 设置段大小，一般为buffer_size的1/2或者1/4；
	if ((err = snd_pcm_hw_params_set_period_size_near(handle,
													  params,
													  &period_size, 0)) < 0)
	{
		LOG(ERROR) << "Set period size error.";
		return -1;
	}
	else
	{
		snd_pcm_uframes_t t_period_size;
		snd_pcm_hw_params_get_period_size(params, &t_period_size, 0);
		if (t_period_size != period_size)
		{
			LOG(WARN) << "Period size " << period_size
					  << " not available, get " << t_period_size << " frames.";
		}
		else
		{
			LOG(INFO) << "Period size set to " << period_size << " frames.";
		}
	}

	// 将参数写入设备
	if ((err = snd_pcm_hw_params(handle, params)) < 0)
	{
		LOG(ERROR) << "Set parameters error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set parameters success.";
		PARAMS_SETED = true;
	}
	return 0;
}
}
}