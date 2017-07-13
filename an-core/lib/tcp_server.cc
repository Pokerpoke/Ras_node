#include <iostream>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "tcp_server.h"

namespace an
{
namespace core
{

tcp_server::tcp_server(int server_port)
{
	tcp_server_init(server_port);
}

int tcp_server::tcp_server_init(int server_port)
{
	if ((listen_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "Create cocket error.";
		return 1;
	}

	// memset(server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(server_port);

	if (bind(listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		std::cerr << "Bind socket error";
		return 2;
	}

	int t_backlog = 10;

	if (listen(listen_socket, t_backlog) == -1)
	{
		std::cerr << "Listen socket error.";
		return 3;
	}

	return 0;
}

int tcp_server::tcp_listen(char *out)
{
	std::clog << "Waiting for client's request ...";

	char buff[4096];

	while (1)
	{
		if ((conn_socket = accept(listen_socket, (struct sockaddr *)NULL, NULL)) == -1)
		{
			std::cerr << "Accept socket error.";
			continue;
		}
		recv(conn_socket, buff, 4096, 0);
		std::cout << buff;
		close(conn_socket);
	}

	return 0;
}

tcp_server::~tcp_server()
{
	close(listen_socket);
}
}
}