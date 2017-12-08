#include <stdio.h>
#include <sched.h>
#include <iostream>

#include "rtp_receiver.h"
#include "voice_playback.h"
#include "logger.h"

using namespace std;
using namespace an::core;

VoicePlayback p("default");

class rtpreceiver : public an::core::RTPReceiver
{
  public:
	rtpreceiver(int port) : an::core::RTPReceiver(port)
	{
	}
	void payload_process()
	{
		p.playback(output_buffer, output_buffer_size);
	}
};

int main()
{
	logger_init();

	rtpreceiver r(13374);
	VoicePlayback p("default");

	r.start_listen();

	return 0;
}