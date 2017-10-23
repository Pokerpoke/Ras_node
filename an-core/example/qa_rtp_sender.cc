#include "rtp_sender.h"
#include "voice_capture.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	RTPSender s("127.0.0.1", 13374);
	VoiceCapture c("default");


	// for (size_t i = 0; i < 10; i++)
	while(1)
	{
		// s.write((char *)"123456", 10);
		c.capture();
		s.write(c.output_buffer, c.output_buffer_size);
	}

	return 0;
}