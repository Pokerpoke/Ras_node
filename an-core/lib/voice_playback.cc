#include "logger.h"
#include "voice_playback.h"

namespace an
{
namespace core
{
VoicePlayback::VoicePlayback(const std::string &device)
{
	if (!DEVICE_OPENED)
		open_device();
	if (!PARAMS_SETED)
		set_params();
}
VoicePlayback::~VoicePlayback()
{
}

int VoicePlayback::open_device()
{
	if ((err = snd_pcm_open(&handle,
							device,
							SND_PCM_STREAM_PLAYBACK,
							0)) < 0)
	{
		LOG(ERROR) << "Playback device open error.";
		DEVICE_OPENED = false;
		return -1;
	}
	else
	{
		LOG(INFO) << "Device \"" << device << "\" open success.";
		DEVICE_OPENED = true;
		snd_pcm_prepare(handle);
	}
	return 0;
}
int VoicePlayback::playback(const char *input_buffer, int input_buffer_size)
{
	int err;
	int r = input_buffer_size;
	while (r > 0)
	{
		// err = snd_pcm_writei(handle, input_buffer, input_buffer_size);
		// err = snd_pcm_writei(handle, input_buffer, frames-4);
		err = snd_pcm_writei(handle, input_buffer, frames);
		if (err == -EPIPE)
		{
			snd_pcm_prepare(handle);
			continue;
		}
		if (err < 0)
		{
			LOG(ERROR) << "Write buffer error for: " << snd_strerror(err);
			return -1;
		}
		r -= err;
		input_buffer += err * 4;
#ifdef ENABLE_DEBUG
		LOG(INFO) << "Write buffer success.";
		LOG(INFO) << snd_pcm_avail(handle);
#endif
	}
	return 0;
}
}
}