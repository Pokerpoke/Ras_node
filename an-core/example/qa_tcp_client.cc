#include <iostream>

#include "tcp_client.h"

using namespace an::core;

int main()
{
	const char *dest_ip = "0.0.0.0";
	const char *data = "hello\n";
	int port = 13374;

	tcp_client t(dest_ip, port);

	if (t.send_data(data) == 0)
	{
		std::clog << "Send success.\n";
	}
	else
	{
		std::clog << "Send failed.\n";
	}

	getchar();
	return 0;
}