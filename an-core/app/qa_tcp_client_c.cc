#include <iostream>

#include "tcp_client_c.h"

using namespace an::core;

int main()
{
	const char *dest_ip = "0.0.0.0";
	const char *data = "hello\n";
	int port = 13374;

	tcp_client_c t;

	t.tcp_client_send_data(dest_ip, port, data);

	getchar();
	return 0;
}