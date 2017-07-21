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
#ifndef _CAM_CAPTURE_H_
#define _CAM_CAPTURE_H_

#include <unistd.h>
#include <linux/videodev2.h>
#include <sys/time.h>

namespace an
{
namespace core
{
namespace cam
{

/** 摄像头捕获类
 * 
 * @brief	摄像头捕获类
 */
class cam_capture
{
  public:
	cam_capture(const char *dev);
	cam_capture();
	cam_capture(cam_capture &&) = default;
	cam_capture(const cam_capture &) = default;
	cam_capture &operator=(cam_capture &&) = default;
	cam_capture &operator=(const cam_capture &) = default;
	~cam_capture();

	int stream_on();
	int stream_off();
	int cam_open(const char *dev);
	int set_pic_width(int width);
	int set_pic_height(int height);
	int capture(void **out, size_t &len);
	int capture_to_file(const char *output_file);

  private:
	int fd;
	fd_set fds;
	struct v4l2_capability cap;
	struct v4l2_format fmt;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	struct timeval tv;

	bool seted_pic_width;
	bool seted_pic_height;
	bool seted_time_out;

	int cam_init(const char *dev);
	int capture(void **out);
	int query_capabilities();
	int set_picture_format();
	int request_buffers();
	int memory_map(void **buffer);
	int memory_unmap(void **buffer);
	int query_buffer();
	int queue_buffer();
	int set_time_out();
	int read_data();
};
}
}
}

#endif // !_CAM_CAPTURE_H_