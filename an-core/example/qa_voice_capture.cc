#include "voice_capture.h"
#include "logger.h"
#include <stdio.h>

// #define _DEBUG

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	int fd;
	fd = open("test.pcm", O_WRONLY | O_CREAT | O_TRUNC, 0664);

	voice_capture capture;
	// voice_capture capture("default");

	int r, loop_sec;
	loop_sec = 2;
	unsigned long loop_limit;
	loop_limit = loop_sec * capture.rate;

	for (size_t i = 0; i < loop_limit; i++)
	{
		r = capture.capture();
		write(fd, capture.output_buffer, capture.output_buffer_size);
		i += r;
#ifdef ENABLE_DEBUG
		cout << "hellop";
#endif
	}

	getchar();

	return 0;
}