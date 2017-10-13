#include <stdio.h>

#include "voice_playback.h"
#include "voice_capture.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	// VoicePlayback p("hw:0,0");
	// VoiceCapture c("hw:0,0");
	VoicePlayback p("default");
	VoiceCapture c("default");

	while (1)
	{
		c.capture();
		p.playback(c.output_buffer, c.output_buffer_size);
	}

	getchar();

	return 0;
}