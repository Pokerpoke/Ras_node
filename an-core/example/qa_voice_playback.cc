#include <stdio.h>

#include "voice_playback.h"
#include "voice_capture.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();
	int fd;
	unsigned long offset;

	VoicePlayback p;
	voice_capture c;

	fd = open("test.pcm", O_RDONLY);

	char *buffer = (char *)malloc(p.default_buffer_size);
	// int size = 129;
	// char *buffer = (char *)malloc(size);

	// for (size_t i = 0; i < 1000; i++)
	while(1)
	{
		offset = read(fd, buffer, p.default_buffer_size);
		lseek(fd, offset, SEEK_CUR);
		p.playback(buffer, p.default_buffer_size);

		// offset = read(fd, buffer, size);
		// lseek(fd, offset, SEEK_CUR);
		// p.playback(buffer, size);

		// c.capture();
		// usleep(200);
		// p.playback(c.output_buffer, c.output_buffer_size);
	}

	free(buffer);

	// getchar();

	return 0;
}