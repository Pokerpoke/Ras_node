/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    rtp接收例程
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
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