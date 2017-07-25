/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file      
 * @author    姜阳
 * @date      2017.07
 * @brief     摄像头捕获类
 * @version   1.0.0
 * 
 */
#include <unistd.h>
#include <string.h>
#include <linux/videodev2.h>
#include <linux/v4l2-mediabus.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "logger.h"
#include "cam_capture.h"

namespace an
{
namespace core
{
namespace cam
{

cam_capture::cam_capture(const char *dev)
{
	cam_init(dev);
}

cam_capture::cam_capture()
{
	cam_init("/dev/video0");
}

/** 初始化相机
 * 
 * @param   dev	设备地址，如/dev/video0
 * 
 */
int cam_capture::cam_init(const char *dev)
{
	// 初始化相关结构体
	memset(&cap, 0, sizeof(cap));
	memset(&fmt, 0, sizeof(fmt));
	memset(&req, 0, sizeof(req));
	memset(&buf, 0, sizeof(buf));
	memset(&tv, 0, sizeof(tv));

	fd = 0;

	cam_open("/dev/video0");

	// 超时初始化
	FD_ZERO(&fds);
	FD_SET(fd, &fds);

	// 初始化标志位
	seted_pic_width = false;
	seted_pic_height = false;
	seted_time_out = false;

	query_capabilities();

	return 0;
}

/** 打开摄像头
 * 
 * @param   dev	设备地址，如/dev/video0
 * @retval  0	成功
 * @retval  -1	打开设备失败
 * 
 */
int cam_capture::cam_open(const char *dev)
{
	if ((fd = open(dev, O_RDWR)) < 0)
	{
		LOG(ERROR) << "Open device failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Open device success.";
		return 0;
	}
}

/** 查询设备信息
 * 
 * @retval	0	成功
 * @retval	-1	查询失败
 * 
 */
int cam_capture::query_capabilities()
{
	if (ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0)
	{
		LOG(ERROR) << "Query capabilities failed.";
		return -1;
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
		return 0;
	}
}

/** 设置抓取图片格式
 * 
 * @retval	0	成功
 * @retval	-1	设置格式失败
 * 
 */
int cam_capture::set_picture_format()
{

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.field = V4L2_FIELD_NONE;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	if (!seted_pic_width)
	{
		set_pic_width(600);
	}
	if (!seted_pic_height)
	{
		set_pic_height(800);
	}

	if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0)
	{
		LOG(ERROR) << "Set pixel format failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Set pixel format success.";
		return 0;
	}
}

/** 设置图片宽度
 * 
 * @param	width	宽度
 * @retval	0		成功
 */
int cam_capture::set_pic_width(int width)
{
	fmt.fmt.pix.width = width;
	seted_pic_width = true;
	return 0;
}

/** 设置图片高度
 * 
 * @param	height	高度
 * @retval	0		成功
 */
int cam_capture::set_pic_height(int height)
{
	fmt.fmt.pix.height = height;
	seted_pic_height = true;
	return 0;
}

/** 请求缓存
 * 
 * @retval	0	成功
 * @retval	-1	请求失败
 * @note	内存映射模式
 */
int cam_capture::request_buffers()
{
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
		return 0;
	}
}

/** 查询缓存
 * 
 */
int cam_capture::query_buffer()
{
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
		return 0;
	}
}

/**	内存映射
 * 
 * @param	buffer	映射用户地址
 * 
 */
int cam_capture::memory_map(void **buffer)
{
	*buffer = mmap(NULL,				   // 映射区开始地址
				   buf.length,			   // 映射区长度
				   PROT_READ | PROT_WRITE, // 期望的内存保护模式
										   // PROT_EXEC、PROT_READ、PROT_WRITE、PROT_NONE
				   MAP_SHARED,			   // 映射对象类型
				   fd,					   // 有效的文件描述符
				   buf.m.offset);		   // 别映射内容的起点
	return 0;
}

int cam_capture::memory_unmap(void **buffer)
{
	if (munmap(*buffer, buf.length) < 0)
	{
		LOG(ERROR) << "Memory unmap failed.";
		return -1;
	}
	LOG(INFO) << "Memory unmap success.";
	return 0;
}
/** 缓存队列
 * 
 */
int cam_capture::queue_buffer()
{
	if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
	{
		LOG(ERROR) << "Queue buffer failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Queue buffer success.";
		return 0;
	}
}

/**	打开串流
 * 
 */
int cam_capture::stream_on()
{
	if (ioctl(fd, VIDIOC_STREAMON, &buf.type) < 0)
	{
		LOG(ERROR) << "Start capture failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Start capture...";
		return 0;
	}
}

/**	关闭串流
 * 
 */
int cam_capture::stream_off()
{
	if (ioctl(fd, VIDIOC_STREAMOFF, &buf.type) < 0)
	{
		LOG(ERROR) << "Stop capture failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Stop capture...";
		return 0;
	}
}

/** 设置访问设备超时
 * 
 */
int cam_capture::set_time_out()
{
	tv.tv_sec = 2;
	if (select(fd + 1, &fds, NULL, NULL, &tv) < 0)
	{
		LOG(ERROR) << "Camera time out.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Waiting for frame...";
		return 0;
	}
}

/**	从设备读取数据
 * 
 */
int cam_capture::read_data()
{
	if (ioctl(fd, VIDIOC_DQBUF, &buf) < 0)
	{
		LOG(ERROR) << "Retrive frame failed.";
		return -1;
	}
	else
	{
		LOG(INFO) << "Retriving frame.";
		return 0;
	}
}

/**	私有捕获函数，不传递buffer的长度,用于类内部捕获
 * 
 */
int cam_capture::capture(void **out)
{
	if (set_picture_format() ||
		request_buffers() ||
		query_buffer() ||
		memory_map(out) ||
		queue_buffer() ||
		stream_on() ||
		set_time_out() ||
		read_data() < 0)
	{
		return -1;
	}

	return 0;
}

/**	捕获函数
 * 
 * @param	out	输出指针
 * @param	len	内存映射后的长度
 * @return	成功返回0
 * 
 */
int cam_capture::capture(void **out, size_t &len)
{
	if (capture(out) < 0)
	{
		return -1;
	}
	len = buf.length;
	return 0;
}

/**	捕获并输出到文件
 * 
 * @param	output_file	输出文件名
 * @return	成功返回0
 * 
 */
int cam_capture::capture_to_file(const char *output_file)
{
	int output_fd;
	void *buffer;
	if (capture(&buffer) < 0)
	{
		return -1;
	}

	if ((output_fd = open(output_file,
						  O_RDWR | O_CREAT,
						  0666)) < 0)
	{
		LOG(ERROR) << "Output file open failed.";
		close(output_fd);
		return -2;
	}
	else
	{
		LOG(INFO) << "Writing to file: " << output_file;
		write(output_fd, buffer, buf.length);
		close(output_fd);
		return 0;
	}
}

cam_capture::~cam_capture()
{
	close(fd);
}
}
}
}