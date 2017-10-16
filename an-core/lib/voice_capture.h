#ifndef _VOICE_CAPTURE_H_
#define _VOICE_CAPTURE_H_

#include "voice_base.h"

namespace an
{
namespace core
{
class VoiceCapture : public VoiceBase
{
  public:
	char *output_buffer;
	unsigned int output_buffer_size;
	// int frames_to_read;
	int frames_readed;

	VoiceCapture(const std::string &dev);
	~VoiceCapture();

	friend std::ostream &operator<<(std::ostream &out, VoiceCapture &in);

	int open_device();
	int capture();

  private:
	int err;
};
}
}

#endif // !_VOICE_CAPTURE_H_