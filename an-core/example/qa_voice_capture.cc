// #include <stdio.h>
#include <fstream>

#include "voice_capture.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	// int fd;
	// fd = open("test.pcm", O_WRONLY | O_CREAT | O_TRUNC, 0664);

	// voice_capture capture;
	// voice_capture capture("default");

	// int r, loop_sec;
	// loop_sec = 10;
	// unsigned long loop_limit;
	// loop_limit = loop_sec * capture.rate;

	// for (size_t i = 0; i < loop_limit; i++)
	// {
	// 	r = capture.capture();
	// 	write(fd, capture.output_buffer, capture.output_buffer_size);
	// 	i += r;
	// }

	// close(fd);

	voice_capture capture;

	ofstream output("test.pcm", ios::trunc | ios::binary);

	int loop_sec;
	loop_sec = 10;
	unsigned long loop_limit;
	loop_limit = loop_sec * capture.rate;

	for (size_t i = 0; i < loop_limit; i++)
	{
		output << capture;
		i += capture.frames_readed;
	}
	output << capture;
	output.close();

	getchar();

	return 0;
}