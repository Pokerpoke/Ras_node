#include <stdio.h>
#include <sched.h>

#include "rtp_sender.h"
#include "voice_capture.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	struct sched_param sched_param;
	if (sched_getparam(0, &sched_param) < 0)
	{
		LOG(ERROR) << "Set scheduler failed.";
		return -1;
	}
	sched_param.sched_priority = sched_get_priority_max(SCHED_RR);
	if (!sched_setscheduler(0, SCHED_RR, &sched_param))
	{
		LOG(INFO) << "Set priority to " << sched_param.sched_priority;
	}

	RTPSender s("127.0.0.1", 13374);
	// RTPSender s("192.168.0.22", 13374);
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