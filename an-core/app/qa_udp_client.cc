#include <iostream>

#include "udp_client.h"

using namespace an::core;

int main()
{
	const char *dest_ip = "127.0.0.1";
	int dest_port = 13374;
	const char *msg = "hello";

	udp_client client(dest_ip, dest_port);
	client.send_data(msg);

	getchar();
	return 0;
}