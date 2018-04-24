/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    创建一个TCP服务端，用以接受数据。
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-14
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 * @example	qa_tcp_server_callback.cc
 * @example	qa_tcp_server_override.cc
 * 
 */
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>

#include "logger.h"
#include "tcp_server.h"

namespace an
{
namespace core
{

/** 
 * @brief   构造函数
 * 
 * 初始化相关变量
 * 
 * @param[in]   server_port	监听端口
 * 
 */
TCPServer::TCPServer(const int server_port)
	: _server_port(server_port)
{
	memset(&_server_addr, 0, sizeof(_server_addr));

	// 设置协议类型
	_server_addr.sin_family = AF_INET;
	// 设置目标IP
	_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// 设置目标端口
	_server_addr.sin_port = htons(server_port);

	_backlog = 20;
	_addrlen = 0;

	_SOCKET_CREATED = false;
	_LISTEN_SOCKET_CLOSED = false;
	_CONN_SOCKET_CLOSED = false;

	output_buffer_size = 4096;

	init();
}

/**
 * @brief	tcp服务器初始化
 * 
 * @return	初始化结果
 * @retval	0	初始化成功
 * @retval	-1	Socket创建失败
 * @retval	-2	Socket绑定失败
 * @retval	-3	Socket监听失败
 * 
 */
int TCPServer::init()
{
	_SOCKET_CREATED = false;

	if ((_listen_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		LOG(ERROR) << "Create cocket error for: "
				   << strerror(errno);
		return -1;
	}
	else if (bind(_listen_socket,
				  (struct sockaddr *)&_server_addr,
				  sizeof(_server_addr)) < 0)
	{
		LOG(ERROR) << "Bind socket error for: "
				   << strerror(errno);
		return -2;
	}
	else if (listen(_listen_socket, _backlog) < 0)
	{
		LOG(ERROR) << "Listen socket error for: "
				   << strerror(errno);
		return -3;
	}
	else
	{
		LOG(INFO) << "Socket created success.";
		_SOCKET_CREATED = true;
		return 0;
	}
}

/** 
 * @brief	等待连接
 * 
 * @return  连接状态
 * @retval	true	已连接
 * @retval	false	未连接
 * 
 */
bool TCPServer::connected()
{
#ifdef ENABLE_DEBUG
	LOG(INFO) << "Waiting for client's request ...";
#endif
	_addrlen = sizeof(_client_addr);
	memset(&_client_addr, 0, sizeof(_client_addr));
	if ((_conn_socket = accept(_listen_socket,
							   (struct sockaddr *)&_client_addr,
							   (socklen_t *)&_addrlen)) < 0)
	{
		LOG(ERROR) << "Accept socket error for: "
				   << strerror(errno);
		return false;
	}
	else
	{
		LOG(INFO) << "Socket accepted: "
				  << inet_ntoa(_client_addr.sin_addr);
		return true;
	}
}

/** 
 * @brief   开始监听
 * 
 * 通过继承该类，并重载payload_process函数进行监听
 * 
 */
int TCPServer::start_listen()
{
	return start_listen([&] {
		this->payload_process();
	});
}

/** 
 * @brief   开始监听
 * 
 * 回调函数方式，传入函数指针或者lambda函数
 * 
 * @param[in]	_payload_process	数据处理函数
 * 
 */
int TCPServer::start_listen(std::function<void(void)> _payload_process)
{
	int n;
	while (1)
	{
		if (connected())
		{
			output_buffer = static_cast<char *>(malloc(output_buffer_size));
			while ((n = recv(_conn_socket,
							 output_buffer,
							 output_buffer_size, 0)) > 0)
			{
				// 回调函数，处理数据
				_payload_process();
			}
			if (n < 0)
				LOG(ERROR) << "Recv error for: "
						   << strerror(errno);
		}
		// @todo	退出循环处理
	}
	close(_conn_socket);
	return 0;
}

/**
 * @brief	关闭Socket
 * 
 */
TCPServer::~TCPServer()
{
	close(_conn_socket);
	close(_listen_socket);
	free(output_buffer);
}
}
}