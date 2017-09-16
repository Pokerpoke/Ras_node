#include "voice_capture.h"
#include "logger.h"

namespace an
{
namespace core
{

voice_capture::voice_capture()
{
	init("default");
}

voice_capture::voice_capture(const char *t_device)
{
	init(t_device);
}

int voice_capture::init(const char *t_device)
{
	device = new char[20];
	strcpy(device, t_device);

	format = SND_PCM_FORMAT_S16_LE;
	channels = 2;
	access_type = SND_PCM_ACCESS_RW_INTERLEAVED;
	rate = 44100;
	frames_to_read = 32;

	DEVICE_OPENED = false;
	PARAMS_SETED = false;

	output_buffer_size = frames_to_read * snd_pcm_format_width(format) / 8 * 2;
	output_buffer = (char *)malloc(output_buffer_size);

	return 0;
}

int voice_capture::open_device()
{

	if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_CAPTURE, 0)) < 0)
	{
		LOG(ERROR) << "Capture device open error.";
		DEVICE_OPENED = false;
		return -1;
	}
	else
	{
		LOG(INFO) << "Device \"" << device << "\" open success.";
		DEVICE_OPENED = true;
	}
	return 0;
}

int voice_capture::set_params()
{
	snd_pcm_hw_params_alloca(&params);

	if ((err = snd_pcm_hw_params_any(handle, params)) < 0)
	{
		LOG(ERROR) << "Initialize parameters error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Initialize parameters success.";
	}

	if ((err = snd_pcm_hw_params_set_access(handle, params, access_type)) < 0)
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

	channels = 2;
	if ((err = snd_pcm_hw_params_set_channels(handle, params, channels)) < 0)
	{
		LOG(ERROR) << "Set channels error.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set channels success.";
	}

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
		PARAMS_SETED = true;
	}
	return 0;
}

int voice_capture::capture()
{
	if (!DEVICE_OPENED)
		open_device();
	if (!PARAMS_SETED)
		set_params();

	if ((frames_readed = snd_pcm_readi(handle, output_buffer, frames_to_read)) < 0)
	{
		LOG(ERROR) << "Read frame error.";
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

std::ostream &operator<<(std::ostream &out, voice_capture &in)
{
	in.capture();
	out.write(in.output_buffer, in.output_buffer_size);
	return out;
}

voice_capture::~voice_capture()
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
	free(output_buffer);
	delete[] device;
}
}
}
