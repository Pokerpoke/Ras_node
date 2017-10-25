#include "rtp_receiver.h"
#include "voice_playback.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	RTPReceiver r(13374);
	VoicePlayback p("default");

	while (1)
	{
		r.read();
		p.playback((char *)r.output_buffer, r.output_buffer_size);
	}

	getchar();
	return 0;
}