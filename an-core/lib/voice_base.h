#ifndef _VOICE_BASE_H_
#define _VOICE_BASE_H_

#include <string>
#include <alsa/asoundlib.h>

namespace an
{
namespace core
{
class VoiceBase
{
  public:
	VoiceBase(const std::string &device);
	virtual ~VoiceBase();

	unsigned int rate;
	unsigned int channels;
	unsigned int soft_resample;
	unsigned int default_buffer_size;
	unsigned int default_period_size;
	unsigned int bytes_per_frame;
	snd_pcm_uframes_t frames;
	snd_pcm_uframes_t buffer_size;
	snd_pcm_uframes_t period_size;

  protected:
	const char *device;

	snd_pcm_t *handle;
	snd_pcm_hw_params_t *params;
	snd_pcm_format_t format;
	snd_pcm_access_t access_type;

	// Flags
	bool PARAMS_SETED;
	bool DEVICE_OPENED;

	int set_params();
	virtual int open_device() = 0;

  private:
	int err;
};
}
}

#endif // !_VOICE_BASE_H_