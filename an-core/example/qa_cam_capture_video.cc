#include <unistd.h>
#include <string.h>
#include <linux/videodev2.h>
#include <linux/v4l2-mediabus.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "logger.h"

int main()
{
	logger_init();

	LOG(INFO) << "test";
	return 0;
}