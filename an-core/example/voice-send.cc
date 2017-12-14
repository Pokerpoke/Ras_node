/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <string>

#include "config.h"
#include "logger.h"
#include "voice_capture.h"
#include "rtp_sender.h"

int main(int argc, char *argv[])
{
	using namespace an::core;
	using namespace std;

	logger_init();
	string dest_ip;

	VoiceCapture c("default");
	if (argc == 1)
	{
		dest_ip = "127.0.0.1";
	}
	else
	{
		dest_ip = argv[1];
	}
	RTPSender s(dest_ip, 8338);

	while (1)
	{
		c.capture();
		s.write(c.output_buffer, c.output_buffer_size);
	}

	return 0;
}