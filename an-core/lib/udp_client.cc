/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author    姜阳
 * @date      2017.07
 * @brief     UDP客户端
 * @version   1.0.0
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

#include "udp_client.h"

namespace an
{
namespace core
{
udp_client::udp_client(const char *dest_ip, int dest_port)
{
	std::memset(&server_addr, 0, sizeof(server_addr));

	// 设置协议类型
	server_addr.sin_family = AF_INET;
	// 设置目标端口
	server_addr.sin_port = htons(dest_port);
	// 设置目标IP
	server_addr.sin_addr.s_addr = inet_addr(dest_ip);
}

/**
 * UDP客户端初始化
 * 
 * @param   NULL
 * @return  成功返回0，失败返回-1。
 * 
 */
int udp_client::init()
{

	// 设置传输模式
	if ((t_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		std::cerr << "Socket create failed.\n";
		return -1;
	}
	return 0;
}

/**
 * 通过UDP协议发送数据
 * 
 * @param   待发送数据
 * @return  成功返回0，初始化失败返回-1。
 * 
 */
int udp_client::send_data(const char *data)
{

	if (init() < 0)
	{
		return -1;
	}

	std::clog << "Sending data...\n";
	if (sendto(t_socket,							// Socket
			   data,								// 发送信息		
			   sizeof(data),						// 信息大小
			   0,									// 标志位
			   (struct sockaddr *)&server_addr,		// 接收端地址
			   sizeof(server_addr)) != 0)			// 接收端地址大小
	{
		std::cerr << strerror(errno) << "\n";
	}

	return 0;
}

udp_client::~udp_client()
{
	close(t_socket);
}
}
}