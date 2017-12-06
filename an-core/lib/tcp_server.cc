/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    创建一个TCP服务端，用以接受数据。
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-02
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <iostream>
#include <string.h>
#include <cstring>
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
	memset(&server_addr, 0, sizeof(server_addr));

	// 设置协议类型
	server_addr.sin_family = AF_INET;
	// 设置目标端口
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// 设置目标IP
	server_addr.sin_port = htons(server_port);

	LISTEN_SOCKET_IS_CLOSED = false;
	CONN_SOCKET_IS_CLOSED = false;

	init();
}

/**
 * tcp服务器初始化。
 * @param   服务端监听端口
 * @TODO: - 异常捕获
 * 		  - 错误代码
 * @return 成功返回0
 * @retval	0	初始化成功
 * @retval	-1	Socket创建失败
 * @retval	-2	Socket绑定失败
 * @retval	-3	Socket监听失败
 * 
 */
int tcp_server::init()
{
	if ((listen_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Create cocket error.\n";
		return -1;
	}

	if (bind(listen_socket,
			 (struct sockaddr *)&server_addr,
			 sizeof(server_addr)) < 0)
	{
		std::cerr << "Bind socket error.\n";
		return -2;
	}

	int t_backlog = 10;

	if (listen(listen_socket, t_backlog) < 0)
	{
		std::cerr << "Listen socket error.\n";
		return -3;
	}

	return 0;
}

/** 等待连接
 * 
 * @return  返回连接状态
 * @retval	0	已连接
 * @retval	-1	未连接，等待连接
 * 
 */
int tcp_server::is_connected()
{
	std::clog << "Waiting for client's request ...\n";
	if ((conn_socket = accept(listen_socket,
							  (struct sockaddr *)NULL,
							  NULL)) < 0)
	{
		std::cerr << "Accept socket error.\n";
		return -1;
	}
	else
	{
		std::clog << "Socket accepted.\n";
		return 0;
	}
}

/**
 * 开始监听
 * 
 * @param[in,out]	out	输出数组
 * @param[in]		len	数组长度
 * @return 			正常结束返回0
 * @warning			会首先将输出数组初始化
 * 
 */
int tcp_server::tcp_receive(char *out, int len)
{
	memset(out, 0, len);

	recv(conn_socket, out, len, 0);

	return 0;
}

/**
 * 关闭连接
 * 
 * @return	成功返回0
 */
int tcp_server::close_connect()
{
	if (!CONN_SOCKET_IS_CLOSED)
	{
		close(conn_socket);
	}
	return 0;
}

/**
 * 关闭Socket
 * 
 */
tcp_server::~tcp_server()
{
	if (!CONN_SOCKET_IS_CLOSED)
	{
		close(conn_socket);
	}
	if (!LISTEN_SOCKET_IS_CLOSED)
	{
		close(listen_socket);
	}
}
}
}