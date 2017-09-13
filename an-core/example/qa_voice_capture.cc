#include <alsa/asoundlib.h>
#include <stdio.h>

#include "logger.h"

using namespace std;

int main()
{
	logger_init();

	const char *device = "hw:0,0";
	snd_pcm_t *handle;
	snd_pcm_t *phandle;
	snd_pcm_hw_params_t *params;
	snd_pcm_hw_params_t *pparams;
	snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
	int err;

	if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_CAPTURE, 0)) < 0)
	{
		LOG(ERROR) << "Capture device open error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Capture device open success.";
	}

	snd_pcm_hw_params_alloca(&params);

	if ((err = snd_pcm_open(&phandle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{
		LOG(ERROR) << "Playback device open error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Playback device open success.";
	}

	if ((err = snd_pcm_set_params(phandle,
								  format,
								  SND_PCM_ACCESS_RW_INTERLEAVED,
								  2,
								  44100,
								  1,
								  500000)) < 0)
	{
		LOG(ERROR) << " error.";
		return -1;
	}
	else
	{
		LOG(INFO) << " success.";
	}

	if ((err = snd_pcm_hw_params_any(handle, params)) < 0)
	{
		LOG(ERROR) << "Initialize parameters error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Initialize parameters success.";
	}

	if ((err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
	{
		LOG(ERROR) << "Set access type error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set access type success.";
	}

	if ((err = snd_pcm_hw_params_set_format(handle, params, format)) < 0)
	{
		LOG(ERROR) << "Set format error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set format success.";
	}

	int channels = 2;
	if ((err = snd_pcm_hw_params_set_channels(handle, params, channels)) < 0)
	{
		LOG(ERROR) << "Set channels error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set channels success.";
	}

	unsigned int rate = 44100;
	unsigned int rrate;
	rrate = rate;
	if ((err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0)) < 0)
	{
		LOG(ERROR) << "Set rate error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set rate to " << rate << "Hz success.";
		if (rrate != rate)
		{
			LOG(WARN) << "Rate " << rrate << "Hz not available, get " << rate << "Hz.";
		}
	}

	if ((err = snd_pcm_hw_params(handle, params)) < 0)
	{
		LOG(ERROR) << "Set parameters error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set parameters success.";
	}

	int loop_sec = 10;
	unsigned long loop_limit;
	loop_limit = loop_sec * rate;
	int latency_min = 8196;
	int latency_max = 8196;
	// int frames = 32;
	size_t frames;
	int latency;
	char *buffer;
	size_t *max;

	latency = latency_min - 4;
	buffer = (char *)malloc(latency_max * snd_pcm_format_width(format) / 8 * 2);

	int fd;
	fd = open("test.pcm", O_WRONLY | O_CREAT, 0664);

	for (size_t i = 0; i < loop_limit; i++)
	{
		long r = 0;
		if ((r = snd_pcm_readi(handle, buffer, latency)) < 0)
		{
			LOG(ERROR) << "Read frames error.";
			return -1;
		}
		else
		{
			i += r;
			LOG(INFO) << "Read frames success.";
			snd_pcm_writei(phandle, buffer, latency);
			write(fd, buffer, latency);
		}
	}

	// snd_pcm_hw_free(handle);
	snd_pcm_close(handle);
	snd_pcm_close(phandle);
	LOG(INFO) << "Close device success.";
	close(fd);

	getchar();
	return 0;
}

void set_riff()
{
}