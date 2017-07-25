#include <fstream>
#include <unistd.h>
#include <string.h>
#include <linux/videodev2.h>
#include <linux/v4l2-mediabus.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string>
#include <sys/time.h>

#include "logger.h"

using namespace std;

int read_frame();
fd_set fds;
struct timeval tv;
unsigned int n_buffers;
int fd = 0;
struct buffer
{
	void *data;
	size_t size;
};
struct buffer *buffers;

int main()
{
	logger_init();

	if ((fd = open("/dev/video0", O_RDWR)) < 0)
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
		LOG(INFO) << "Query capabilities success.\n\t"
				  << "Driver:       " << cap.driver << "\n\t"
				  << "Card:         " << cap.card << "\n\t"
				  << "Bus info:     " << cap.bus_info << "\n\t"
				  << "Version:      " << (cap.version >> 16 & 0xFF)
				  << "." << (cap.version >> 8 & 0xFF)
				  << "." << (cap.version & 0xFF) << "\n\t"
				  << "Capabilities: " << cap.capabilities;
	}

	// Set format
	struct v4l2_format fmt = {0};
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = 640;
	fmt.fmt.pix.height = 480;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	fmt.fmt.pix.field = V4L2_FIELD_ANY;

	if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0)
	{
		LOG(ERROR) << "Set format failed.";
	}
	else
	{
		LOG(INFO) << "Set format success.\n\t"
				  << "Width:        " << fmt.fmt.pix.width << "\n\t"
				  << "Height:       " << fmt.fmt.pix.height << "\n\t";
	}

	// Request buffer
	struct v4l2_requestbuffers req = {0};
	req.count = 4;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	if (ioctl(fd, VIDIOC_REQBUFS, &req) < 0)
	{
		LOG(ERROR) << "Request buffers failed.";
	}
	else
	{
		LOG(INFO) << "Request buffers success.";
	}

	// Query buffer and Map buffer and Stream on
	buffers = (buffer *)calloc(req.count, sizeof(*buffers));

	for (n_buffers = 0; n_buffers < req.count; n_buffers++)
	{

		struct v4l2_buffer buf = {0};
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;

		if (ioctl(fd, VIDIOC_QUERYBUF, &buf) < 0)
		{
			LOG(ERROR) << "Query buffer failed.";
		}
		else
		{
			LOG(INFO) << "Query buffer success.";

			buffers[n_buffers].size = buf.length;
			buffers[n_buffers].data = mmap(NULL,
										   buf.length,
										   PROT_READ | PROT_WRITE,
										   MAP_SHARED,
										   fd,
										   buf.m.offset);
			if (buffers[n_buffers].data == MAP_FAILED)
			{
				LOG(ERROR) << "Map failed.";
			}

			if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
			{
				LOG(ERROR) << "Qbuf failed.";
			}
			else
			{
				LOG(INFO) << "Qbuf success.";
			}
		}
		if ((ioctl(fd, VIDIOC_STREAMON, &buf.type) < 0) &&
			(n_buffers == req.count - 1))
		{
			LOG(ERROR) << "Stream on failed.";
		}
		else
		{
			LOG(INFO) << "Stream on success.";
		}
	}

	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	tv.tv_sec = 2;
	if (select(fd + 1, &fds, NULL, NULL, &tv) < 0)
	{
		LOG(ERROR) << "Set time out failed.";
	}
	else
	{
		LOG(INFO) << "Set time out success.";
	}

	while (1)
	{
		read_frame();
	}

	close(fd);
	getchar();
	return 0;
}

int read_frame()
{
	for (size_t i = 0; i < n_buffers; i++)
	{
		struct v4l2_buffer buf = {0};
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;

		if (ioctl(fd, VIDIOC_DQBUF, &buf) < 0)
		{
			LOG(ERROR) << "Dqbuf failed.";
		}
		else
		{
			LOG(INFO) << "Dqbuf success.";
		}

		string output_file = "test";
		output_file += to_string(i);
		output_file += ".jpg";
		ofstream image(output_file);
		image.write((char *)buffers[i].data, buffers[i].size);
		image.close();

		if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
		{
			LOG(ERROR) << "qbuf failed." << i;
		}
		else
		{
			LOG(INFO) << "qbuf success." << i;
		}
	}
}