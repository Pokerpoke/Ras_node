#include "logger.h"
#include "cam_capture.h"

using namespace an::core::cam;

#define _DEBUG 0

int main()
{
	logger_init(AN_LOG_INFO);

	cam_capture cam;

	cam.capture_to_file("test.jpg");

	getchar();
	return 0;
}