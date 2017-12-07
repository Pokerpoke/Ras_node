/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    音频回放例程
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-07
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <stdio.h>

#include "logger.h"
#include "voice_playback.h"

using namespace std;
using namespace an::core;

int main(int argc, char *argv[])
{
	logger_init();

	VoicePlayback p("default");

	int fd = open("test.pcm", O_RDONLY);

	if (fd < 0)
	{
		LOG(ERROR) << "File open failed";
		return -1;
	}

	int input_buffer_size = p.default_buffer_size;
	char *input_buffer;

	input_buffer = (char *)malloc(input_buffer_size);

	while (read(fd, input_buffer, input_buffer_size) > 0)
	{
		p.playback(input_buffer, input_buffer_size);
	}

	close(fd);
	free(input_buffer);

	return 0;
}