#include "logger.h"
#include "voice_capture.h"

namespace an
{
namespace core
{
VoiceCapture::VoiceCapture(const std::string &device)
{
	frames_to_read = 32;

	output_buffer = (char *)malloc(frames_to_read * bytes_per_frame);
	output_buffer_size = frames_to_read * bytes_per_frame;

	if (!DEVICE_OPENED)
		open_device();
	if (!PARAMS_SETED)
		set_params();
}

VoiceCapture::~VoiceCapture()
{
	free(output_buffer);
}

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

int VoiceCapture::capture()
{
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

std::ostream &operator<<(std::ostream &out, VoiceCapture &in)
{
	in.capture();
	out.write(in.output_buffer, in.output_buffer_size);
	return out;
}
}
}