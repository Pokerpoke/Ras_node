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

	int cam_open(const char *dev);
	int query_capabilities();
	int set_picture_format();
	int request_buffers();
	int query_buffer();
	// int memory_map(void *buffer);
	int memory_map(void *buffer);
	int queue_buffer();
	int stream_on();
	int stream_off();
	int set_time_out();
	int read_data();
	int capture(void *out);
	// int capture(void *out);
	int capture_to_file(const char *output_file);

  private:
	int fd;
	fd_set fds;
	struct v4l2_capability cap;
	struct v4l2_format fmt;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	struct timeval tv;
};
}
}
}

#endif // !_CAM_CAPTURE_H_