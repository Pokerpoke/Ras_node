#include <iostream>
#include <unistd.h>
#include <cstring>

#include "udp_server.h"

using namespace an::core;

int main()
{
	int port = 13374;
	char temp[1024];

	udp_server s(port);

	while (1)
	{
		if (s.udp_listen(temp, sizeof(temp)) == 0)
		{
			std::cout << temp;
		}
	}
	return 0;
}