/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file      udp_client.cc
 * @author    姜阳
 * @date      2017.07
 * @brief     udp客户端
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

int udp_client::send_data(const char *data)
{

	if (init() < 0)
	{
		return -1;
	}

	std::clog << "Sending data...\n";
	sendto(t_socket, data, sizeof(data), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

	return 0;
}

udp_client::~udp_client()
{
	close(t_socket);
}
}
}