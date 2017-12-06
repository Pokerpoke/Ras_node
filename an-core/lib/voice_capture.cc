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
 * Last Modified:  2017-12-02
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "logger.h"
#include "voice_capture.h"

namespace an
{
namespace core
{
/** 
 * @brief 音频捕获构造函数，分配输出缓存空间
 * 
 * @param	dev 设备名称，可以传入default
 * 
 */
VoiceCapture::VoiceCapture(const std::string &dev) : VoiceBase(dev)
{
	// frames_to_read = 32;

	output_buffer_size = frames * bytes_per_frame;
	output_buffer = (char *)malloc(output_buffer_size);

	if (!DEVICE_OPENED)
		open_device();
	if (!PARAMS_SETED)
		set_params();
}

/** 
 * @brief 音频捕获析构函数，释放输出缓存
 * 
 */
VoiceCapture::~VoiceCapture()
{
	free(output_buffer);
}

/** 
 * @brief 打开设备
 * 
 * @retval	0	成功 
 * @retval	-1	失败	  
 * 
 */
int VoiceCapture::open_device()
{
	if ((err = snd_pcm_open(&handle,
							device,
							SND_PCM_STREAM_CAPTURE,
							0)) < 0)
	{
		LOG(ERROR) << "Capture device open error.";
		DEVICE_OPENED = false;
		return -1;
	}
	else
	{
		LOG(INFO) << "Capture device \"" << device << "\" open success.";
		DEVICE_OPENED = true;
	}

	return 0;
}

/** 
 * @brief 音频捕获
 * 
 * 使用capture.output_buffer和capture.output_buffer_size来获取输出数据
 * 
 * @todo 返回类或者结构体
 * 
 */
int VoiceCapture::capture()
{
	while (1)
	{
		if ((frames_readed = snd_pcm_readi(handle, output_buffer, frames)) < 0)
		{
			// Overrun happened
			if (frames_readed == -EPIPE)
			{
				// snd_pcm_recover(handle, frames_readed, 0);
				snd_pcm_prepare(handle);
				continue;
			}
			LOG(ERROR) << "Read frame error for: " << snd_strerror(frames_readed);
			return -1;
		}
		else
		{
#ifdef ENABLE_DEBUG
			LOG(INFO) << "Read frames success.";
#endif
			return frames_readed;
		}
	}
}

/** 
 * @brief 重载<<运算符
 * 
 */
std::ostream &operator<<(std::ostream &out, VoiceCapture &in)
{
	in.capture();
	out.write(in.output_buffer, in.output_buffer_size);
	return out;
}
}
}