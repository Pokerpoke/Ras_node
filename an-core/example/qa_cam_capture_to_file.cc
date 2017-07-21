#include "logger.h"
#include "cam_capture.h"

using namespace an::core::cam;

int main()
{
	logger_init(AN_LOG_INFO);

	cam_capture cam;

	cam.capture_to_file("test.jpg");

	return 0;
}