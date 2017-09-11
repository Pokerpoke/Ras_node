#include <iostream>
#include <fstream>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <alsa/asoundlib.h>
#include <stdio.h>

#include "logger.h"

using namespace std;

int main()
{
	logger_init();

	// unsigned char buffer[16 * 1024];
	int err;
	// unsigned int rate = 44100;
	unsigned int rate = 8000;
	int buffer_frames = 32;
	snd_pcm_t *capture_handle;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_uframes_t frames = 32;

	// 打开设备
	// if ((err = snd_pcm_open(&capture_handle, "plughw:0,0", SND_PCM_STREAM_CAPTURE, 0)) < 0)
	if ((err = snd_pcm_open(&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0)) < 0)
	{
		LOG(ERROR) << "Device open error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Device open success.\n";
	}

	// 分配参数空间
	// if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0)
	// {
	// 	LOG(ERROR) << "Allocate hardware parameter error: " << snd_strerror(err) << "\n";
	// 	return -1;
	// }
	// else
	// {
	// 	LOG(INFO) << "Allocate hardware parameter success.\n";
	// }
	snd_pcm_hw_params_alloca(&hw_params);

	// 初始化参数配置
	if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0)
	{
		LOG(ERROR) << "Initialize hardware parameter error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Initialize hardware parameter success.\n";
	}

	// 设定访问方式，交错读写
	if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
	{
		LOG(ERROR) << "Set access type error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set access type success.\n";
	}

	if ((err = snd_pcm_hw_params_set_rate_resample(capture_handle, hw_params, 1)) < 0)
	{
		LOG(ERROR) << "Set resample error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set resample success.\n";
	}

	// 设定采集格式，signed 16 little endian
	snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
	if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, format)) < 0)
	{
		LOG(ERROR) << "Set format error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set format success.\n";
	}

	// 设定采集码率，44100Hz
	if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0)) < 0)
	{
		LOG(ERROR) << "Set rate error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set rate success.\n";
	}

	if ((err = snd_pcm_hw_params_set_period_size_near(capture_handle, hw_params, &frames, 0)) < 0)
	{
		LOG(ERROR) << "Set period error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set period success.\n";
	}
	// 设定通道，双通道
	if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0)
	{
		LOG(ERROR) << "Set channels error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set channels success.\n";
	}

	// 设定参数
	if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0)
	{
		LOG(ERROR) << "Set parameters error: " << snd_strerror(err) << "\n";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set parameters success.\n";
	}

	// 释放指针
	// snd_pcm_hw_params_free(hw_params);

	// // 准备设备
	// if ((err = snd_pcm_prepare(capture_handle)) < 0)
	// {
	// 	LOG(ERROR) << "Device prepare error: " << snd_strerror(err) << "\n";
	// 	return -1;
	// }
	// else
	// {
	// 	LOG(INFO) << "Device prepare success.\n";
	// }

	int *buffer;
	// buffer = (char *)malloc(buffer_frames * snd_pcm_format_width(format) / 8 * 2);
	buffer = (int *)malloc(buffer_frames * 16 / 8 * 2);

	// ofstream out("test.pcm", ios::out);
	int fd;
	fd = open("test.pcm", O_RDWR | O_CREAT | O_TRUNC, 0664);
	uint32_t duration;
	// duration = 3000000;

	// for (uint32_t i = 0; i < (duration * 1000 * 1000 / rate / buffer_frames); i++)
	for (uint32_t i = 0; i < 100000; i++)
	{
		if ((err = snd_pcm_readi(capture_handle, buffer, frames)) != frames)
		{
			LOG(ERROR) << "Read from device error: " << snd_strerror(err) << "\n";
			return -1;
		}
		else
		{
			LOG(INFO) << "Read from device success.";
			write(fd, buffer, sizeof(buffer));
		}
	}

	// out.close();
	close(fd);
	free(buffer);
	snd_pcm_close(capture_handle);
	LOG(INFO) << "Device close success.\n";

	getchar();
	return 0;
}