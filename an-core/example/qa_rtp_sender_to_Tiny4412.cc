#include "rtp_sender.h"
#include "voice_capture.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	RTPSender s("192.168.0.22", 13374);
	VoiceCapture c("default");


	// for (size_t i = 0; i < 10; i++)
	while(1)
	{
		// s.write((char *)"1234567890", 10);
		c.capture();
		s.write(c.output_buffer, c.output_buffer_size);
	}

	return 0;
}