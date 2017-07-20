#include <unistd.h>
#include <linux/videodev2.h>
#include <linux/v4l2-mediabus.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "logger.h"
#include "cam_capture.h"

int main()
{
	logger_init(AN_LOG_INFO);

	// 打开设备
	const char *dev = "/dev/video0";
	int fd;

	// 组摄方式打开阻塞时使用非阻塞方式打开,阻塞方式打开可能会导致卡在VIDIOC_DQBUF过程
	// if ((fd = open(dev, O_RDWR | O_NONBLOCK)) == -1)
	if ((fd = open(dev, O_RDWR)) == -1)
	{
		LOG(ERROR) << "Open device failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Open device success.";
	}

	// 获取设备信息
	struct v4l2_capability cap = {0};

	if (ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0)
	{
		LOG(ERROR) << "Query capabilities failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Query capabilities success.\n\t"
				  << "Drive: " << cap.driver << "\n\t"
				  << "Card: " << cap.card << "\n\t"
				  << "Bus info: " << cap.bus_info << "\n\t"
				  << "Version: " << cap.version << "\n\t"
				  << "Capabilities: " << cap.capabilities;
	}

	// 设置图像大小格式
	struct v4l2_format fmt = {0};

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = 600;
	fmt.fmt.pix.height = 800;
	fmt.fmt.pix.field = V4L2_FIELD_NONE;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	// fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0)
	{
		LOG(ERROR) << "Set pixel format failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set pixel format success.";
	}

	// 申请缓存
	struct v4l2_requestbuffers req = {0};

	req.count = 1;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	if (ioctl(fd, VIDIOC_REQBUFS, &req) < 0)
	{
		LOG(ERROR) << "Require buffer failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Require buffer success.";
	}

	// 获取捕获
	void *buffer;
	struct v4l2_buffer buf = {0};

	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	buf.index = 0;
	if (ioctl(fd, VIDIOC_QUERYBUF, &buf) < 0)
	{
		LOG(ERROR) << "Query buffer failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Query buffer success.";
	}
	buffer = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);

	// 队列缓存
	if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
	{
		LOG(ERROR) << "Queen buffer failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Queen buffer success.";
	}

	// 开始捕获
	if (ioctl(fd, VIDIOC_STREAMON, &buf.type) < 0)
	{
		LOG(ERROR) << "Start capture failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Start capture.";
	}

	// 异步操作？
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	struct timeval tv = {0};

	tv.tv_sec = 2;
	if (select(fd + 1, &fds, NULL, NULL, &tv) < 0)
	{
		LOG(ERROR) << "Monitor file failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Waiting for frame.";
	}

	// 获取数据
	if (ioctl(fd, VIDIOC_DQBUF, &buf) < 0)
	{
		LOG(ERROR) << "Retrive frame failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Retriving frame.";
	}

	// 输出到文件
	int output_file;
	// if ((output_file = open("test.yuv", O_RDWR | O_CREAT, 0666)) < 0)
	if ((output_file = open("test.jpg", O_RDWR | O_CREAT, 0666)) < 0)
	{
		LOG(ERROR) << "Output file open failed.";
		close(output_file);
		return -1;
	}
	else
	{
		write(output_file, buffer, buf.length);
	}

	close(fd);
	LOG(INFO) << "Close device.";

	// getchar();
	return 0;
}