/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    创建一个UDP服务端
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-14
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>

#include "logger.h"
#include "udp_server.h"

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
UDPServer::UDPServer(const int server_port)
	: _server_port(server_port)
{
	memset(&_server_addr, 0, sizeof(_server_addr));

	_server_addr.sin_family = AF_INET;
	_server_addr.sin_port = htons(_server_port);
	_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	output_buffer_size = 4096;
	_SOCKET_CREATED = false;

	_len = sizeof(_server_addr);
	output_buffer = (char *)malloc(output_buffer_size);

	init();
}

/** 
 * @brief	初始化
 * 
 * @return  0,-1,-2
 * @retval	0	正常结束
 * @retval	-1	Socket创建失败
 * @retval	-2	Socket绑定失败
 * 
 */
int UDPServer::init()
{
	_SOCKET_CREATED = false;
	if ((_socket = socket(AF_INET,
						  SOCK_DGRAM,
						  IPPROTO_UDP)) < 0)
	{
		LOG(ERROR) << "Socket create failed for: "
				   << strerror(errno);
		return -1;
	}

	if (bind(_socket,
			 (struct sockaddr *)&_server_addr,
			 sizeof(_server_addr)) < 0)
	{
		LOG(ERROR) << "Socket bind failed for: "
				   << strerror(errno);
		return -2;
	}
	_SOCKET_CREATED = true;
	return 0;
}

/** 
 * @brief   开始监听
 * 
 * 通过继承该类，并重载payload_process函数进行监听
 * 
 */
int UDPServer::start_listen()
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
int UDPServer::start_listen(std::function<void(void)> _payload_process)
{
	while (1)
	{
		if ((_err = recvfrom(_socket,						   // 套接字
							 output_buffer,					   // 输出缓存
							 output_buffer_size,			   // 输出缓存大小
							 0,								   // 标志位
							 (struct sockaddr *)&_server_addr, // 发送方地址
							 &_len)) < 0)					   // 地址长度
		{
			LOG(ERROR) << "Receive failed for: "
					   << strerror(errno);
		}
		else
		{
			_payload_process();
			// clear
			memset(output_buffer, 0, output_buffer_size);
		}
	}
	return _err;
}

/**
 * @brief	析构函数
 * 
 * 关闭Socket
 * 
 */
UDPServer::~UDPServer()
{
	close(_socket);
	free(output_buffer);
}
}
}
