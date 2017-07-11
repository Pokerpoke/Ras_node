#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "udp_client.h"

int udp_socket_init()
{
	int this_socket;
	struct sockaddr_in dest;
}