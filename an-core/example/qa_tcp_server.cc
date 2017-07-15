#include <iostream>

#include "tcp_server.h"

using namespace an::core;

int main()
{
	int port = 13374;
	char out[4096];

	tcp_server s(13374);

	while (s.is_connected() == 0)
	{
		while (1)
		{
			s.tcp_receive(out, sizeof(out));
			std::cout << out;
		}
	}
	return 0;
}