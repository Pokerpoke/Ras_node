#include "logger.h"
#include "voice_base.h"

namespace an
{
namespace core
{
VoiceBase::VoiceBase(const std::string &dev)
{
	device = dev.c_str();
	channels = 2;
	rate = 44100;
	frames = 32;
	soft_resample = 1;
	format = SND_PCM_FORMAT_S16_LE;
	access_type = SND_PCM_ACCESS_RW_INTERLEAVED;

	DEVICE_OPENED = false;
	PARAMS_SETED = false;

	default_buffer_size = frames * snd_pcm_format_width(format) / 8 * 2;
}

int VoiceBase::set_params()
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
}
}