#include <stdio.h>

#include "voice_playback.h"
#include "voice_capture.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	// VoicePlayback p();
	VoicePlayback p("111");
	VoiceCapture c("11");

	// while (1)
	// {
		c.capture();
		p.playback(c.output_buffer, c.output_buffer_size);
	// }

	getchar();

	return 0;
}