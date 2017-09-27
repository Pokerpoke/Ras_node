#ifndef _VOICE_PLAYBACK_H_
#define _VOICE_PLAYBACK_H_

#include "voice_base.h"

namespace an
{
namespace core
{
class VoicePlayback : public VoiceBase
{
  public:
	VoicePlayback(const std::string &dev = "default");
	~VoicePlayback();

	int open_device();
	int playback(const char *input_buffer, const long input_buffer_size) const;

  private:
	int err;
};
}
}

#endif // !_VOICE_PLAYBACK_H_