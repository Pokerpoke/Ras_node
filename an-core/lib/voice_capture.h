#ifndef _VOICE_CAPTURE_H_
#define _VOICE_CAPTURE_H_

#include <alsa/asoundlib.h>

namespace an
{
namespace core
{
class voice_capture
{
  public:
	char *output_buffer;
	int channels;
	int frames_to_read;
	unsigned int output_buffer_size;
	unsigned int rate;

	voice_capture();
	voice_capture(const char *t_device);
	voice_capture(voice_capture &&) = default;
	voice_capture(const voice_capture &) = default;
	voice_capture &operator=(voice_capture &&) = default;
	voice_capture &operator=(const voice_capture &) = default;
	~voice_capture();

	int capture();

  private:
	char *device;
	int err, frames_readed;
	bool DEVICE_OPENED;
	bool PARAMS_SETED;
	snd_pcm_t *handle;
	snd_pcm_hw_params_t *params;
	snd_pcm_format_t format;
	snd_pcm_access_t access_type;

	int open_device();
	int set_params();
};
}
}

#endif // !_VOICE_CAPTURE_H_