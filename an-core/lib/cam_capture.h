/*******************************************************************************
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    摄像头捕获类
 * @version  0.0.1
 * 
 * Last Modified:  2018-01-18
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 ******************************************************************************/
#ifndef _CAM_CAPTURE_H_
#define _CAM_CAPTURE_H_

#include <string>
#include <functional>
#include <linux/videodev2.h>
#include <sys/time.h>

namespace an
{
namespace core
{
class CamCapture
{
  public:
    CamCapture(const std::string &dev);
    ~CamCapture();

    int capture(std::function<void(void)> data_process);
    int capture();
    int init();

    mutable void *output_buffer;
    mutable int output_buffer_size;

  protected:
    class buffer
    {
      public:
        void *start;
        size_t length;
    };

  private:
    int open_device();
    int query_capabilities();
    int set_pic_width(const int width);
    int set_pic_height(const int height);
    int set_picture_format();
    int request_buffers();
    int memory_map();
    int memory_unmap();
    int query_buffer();
    int queue_buffer();
    int read_frame();
    int stream_on();
    int stream_off();
    int set_time_out(const int t);
    int set_time_out();

    void _data_process();

    const char *_dev;

    buffer *buffers;

    int _fd;
    int _nbuffers;
    fd_set _fds;
    struct timeval _tv;
    struct v4l2_format _fmt;
    struct v4l2_buffer _buf;
    struct v4l2_capability _cap;
    struct v4l2_requestbuffers _req;

    // Flags
    bool INITED;
};
}
}

#endif // !_CAM_CAPTURE_H_