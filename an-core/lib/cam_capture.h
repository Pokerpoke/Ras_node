/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    摄像头捕获类
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-02
 * Modified By:    姜阳 (j824544269@gmail.com)
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

class buffers
{
  public:
	buffers();
	~buffers();

	void *data;
	size_t size;
};

/** 摄像头捕获类
 * 
 * @brief	摄像头捕获类
 */
class cam_capture
{
  public:
	cam_capture(const char *dev);
	cam_capture();
	~cam_capture();

	int cam_open(const char *dev);
	int set_pic_width(int width);
	int set_pic_height(int height);
	int set_time_out(int t);
	int capture(void **out, size_t &len);
	int capture_to_file(const char *output_file);
	int capture_stream_to_file(const char *output_file, int pic_num);

  private:
	int fd;
	int nbuffers;
	fd_set fds;
	struct v4l2_capability cap;
	struct v4l2_format fmt;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	struct timeval tv;

	buffers *buffer;

	bool inited_cam;
	bool seted_pic_width;
	bool seted_pic_height;
	bool seted_time_out;
	bool capture_stream;

	int cam_init(const char *dev);
	int capture(void **out);
	int query_capabilities();
	int set_picture_format();
	int request_buffers();
	int memory_map(void **buffer);
	int memory_map();
	int memory_unmap(void **buffer);
	int memory_unmap();
	int query_buffer();
	int queue_buffer();
	int set_time_out();
	int read_frame();
	int stream_on();
	int stream_off();
};
}
}
}

#endif // !_CAM_CAPTURE_H_