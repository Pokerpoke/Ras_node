/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file      
 * @author    姜阳
 * @date      2017.10
 * @brief     音频采集、回放例程
 * @version   0.0.1
 * 
 */
#include <stdio.h>
#include <sched.h>

#include "voice_playback.h"
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