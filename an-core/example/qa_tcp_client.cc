#include <iostream>

#include "tcp_client.h"

using namespace an::core;

int main()
{
	const char *dest_ip = "0.0.0.0";
	const char *data = "hello\n";
	std::string data2;
	int port = 13374;

	tcp_client t(dest_ip, port);

	while (t.is_connected() == 0)
	{
		t.send_data(data);
		while (1)
		{
			std::cout << "Input data to send ...\n";
			std::cout << "> ";
			std::cin >> data2;
			data2 += "\n";
			t.send_data(data2);
		}
	}

	getchar();
	return 0;
}