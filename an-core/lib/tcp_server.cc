/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file     tcp_server.h
 * @author   姜阳
 * @date     2017.07
 * @brief    创建一个tcp服务端，用以接受数据。
 * @version  1.0.0
 * 
 */

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

/**
 * tcp服务器初始化。
 * @param : 服务端监听端口
 * @TODO: - 异常捕获
 * 		  - 错误代码
 * @return 成功返回0
 * 
 */
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

/**
 * 开始监听
 * @param 输出数组
 * @return 正常结束返回0。
 * 
 */
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