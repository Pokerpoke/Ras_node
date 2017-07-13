#include <iostream>
#include "udp_client.h"

using namespace an::core;

int main(int argc, char **argv)
{
	const char *dest_ip = "127.0.0.1";
	const char *dest_port = "13374";
	const char *msg = "hello";

	udp_client client(dest_ip, dest_port);
	client.send(msg);

	getchar();
	return 0;
}