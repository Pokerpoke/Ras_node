#include <unistd.h>

#include "rtp_sender.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	RTPSender s("192.168.0.7", 13374);


	for (size_t i = 0; i < 10; i++)
	// while(1)
	{
		s.write((char *)"12345678\n", 9);
		sleep(1);
	}

	return 0;
}