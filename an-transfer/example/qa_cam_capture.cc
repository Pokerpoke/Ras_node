#include <iostream>

#include <unistd.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

#include "logger.h"
#include "cam_capture.h"

int main()
{
	logger_init(AN_LOG_INFO);

	const char *dev = "/dev/video0";
	int fd;
	if ((fd = open(dev, O_RDWR) == -1))
	{
		LOG(ERROR) << "Open device failed.";
	}
	else
	{
		LOG(INFO) << "Open device success.";
	}

	struct v4l2_capability cap = {0};
	if (ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0)
	{
		LOG(ERROR) << "Query capabilities failed.";
	}
	else
	{
		LOG(INFO) << "Query capabilities success.";
		LOG(INFO) << "Drive: " << cap.driver;
	}

	close(fd);
	LOG(INFO) << "Close device.";

	getchar();
	return 0;
}