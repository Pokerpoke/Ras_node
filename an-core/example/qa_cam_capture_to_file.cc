#include "logger.h"
#include "cam_capture.h"

using namespace an::core::cam;

int main()
{
	logger_init(AN_LOG_INFO);

	cam_capture cam;

	while (1)
	{
		if (cam.capture_to_file("test.jpg") < 0)
		{
			LOG(ERROR) << "Capture failed.";
			return -1;
		}
	}

	return 0;
}