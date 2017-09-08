#include "logger.h"
#include "cam_capture.h"

using namespace an::core::cam;

int main()
{
	logger_init(AN_LOG_INFO);

	cam_capture cam;

	while (1)
	{
		cam.capture_stream_to_file("test.jpg", 1000);
	}
	// if (cam.capture_stream_to_file("test.jpg", 1000) < 0)
	// {
	// 	LOG(ERROR) << "Capture failed.";
	// 	// return -1;
	// }

	return 0;
}