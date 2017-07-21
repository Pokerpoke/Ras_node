#include "logger.h"
#include "cam_capture.h"

using namespace an::core::cam;

#define _DEBUG 0

int main()
{
	logger_init(AN_LOG_INFO);

	cam_capture cam;

	// cam.capture_to_file("test.jpg");

	int output_fd;
	size_t len;
	void *buffer;
	const char *output_file = "test.jpg";

	cam.capture(&buffer, len);

	if ((output_fd = open(output_file,
						  O_RDWR | O_CREAT,
						  0666)) < 0)
	{
		LOG(ERROR) << "Output file open failed.";
		close(output_fd);
		return -1;
	}
	else
	{
		LOG(INFO) << "Writing to file: " << output_file;
		write(output_fd, buffer, len);
		close(output_fd);
		return 0;
	}

	getchar();
	return 0;
}