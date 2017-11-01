#include <stdio.h>
#include <sched.h>

#include "rtp_receiver.h"
#include "voice_playback.h"
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