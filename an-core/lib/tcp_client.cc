/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author    姜阳
 * @date      2017.07
 * @brief     建立tcp连接并传递数据信息
 * @version   1.0.0
 * 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "tcp_client.h"

namespace an
{
namespace core
{

/** 
 * 
 * @param[in]   目标IP地址
 * @param[in]   目标端口
 * 
 */
tcp_client::tcp_client(const char *dest_ip, int dest_port)
{
	memset(&server_addr, 0, sizeof(server_addr));

	// 设置协议类型
	server_addr.sin_family = AF_INET;
	// 设置目标端口
	server_addr.sin_port = htons(dest_port);
	// 设置目标IP
	server_addr.sin_addr.s_addr = inet_addr(dest_ip);

	init();
}

/**
 * 初始化tcp连接
 * 
 * @param	socked字
 * @return	初始化结果
 * @retval	0	连接成功
 * @retval	-1	Socket创建失败
 */
int tcp_client::init()
{

	// 设置传输模式
	if ((t_socket = socket(AF_INET,
						   SOCK_STREAM,
						   IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket creation failed.\n";
		return -1;
	}

	return 0;
}

/** 连接状态
 * 
 * @return  连接状态
 * @retval	0	成功
 * @retval	-1	连接失败
 * 
 */
int tcp_client::is_connected()
{
	if (connect(t_socket,
				(struct sockaddr *)&server_addr,
				sizeof(server_addr)) != 0)
	{
		std::cerr << "Connected failed.\n";
		return -1;
	}
	std::clog << "Connected.\n";
	return 0;
}

/**
 * 发送数据信息
 * @param[in]	 char类型的数据信息
 * @return		 发送状态
 * @retval		 0	发送成功
 * @retval		 -1	发送失败
 */
int tcp_client::send_data(const char *data)
{

	std::clog << "Sending data...\n";

	if (send(t_socket,
			 data,
			 sizeof(data) - 1,
			 0) < 0)
	{
		std::clog << "Send failed.\n";
		return -1;
	}
	else
	{
		std::clog << "Send success.\n";
		return 0;
	}
}

int tcp_client::send_data(std::string data)
{

	std::clog << "Sending data...\n";

	if (send(t_socket,
			 data.data(),
			 data.size(),
			 0) < 0)
	{
		std::clog << "Send failed.\n";
		return -1;
	}
	else
	{
		std::clog << "Send success.\n";
		return 0;
	}
}

// TODO:文件流传输

tcp_client::~tcp_client()
{
	close(t_socket);
}
}
}
