#include "rtp_sender.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	RTPSender s("192.168.0.22", 13374);


	// for (size_t i = 0; i < 10; i++)
	while(1)
	{
		s.write((char *)"123", 3);
	}

	return 0;
}