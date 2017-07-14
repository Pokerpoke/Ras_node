
/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file      tcp_client.cc
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

tcp_client::tcp_client(const char *dest_ip, int dest_port)
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
 * 初始化tcp连接
 * @param socked字
 * @param 目标地址
 * @param 目标ip
 * @return 成功返回0，socket创建失败返回-1，连接失败返回-2
 */
int tcp_client::init()
{

	// 设置传输模式
	if ((t_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cerr << "Socket creation failed.\n";
		return -1;
	}

	if (connect(t_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
	{
		std::cerr << "Connected failed.\n";
		return -2;
	}
	std::clog << "Connected.\n";

	return 0;
}

/**
 * 发送数据信息
 * @param 目标ip
 * @param 目标端口
 * @param char类型的数据信息
 * @return 成功返回0
 */
int tcp_client::send_data(const char *data)
{

	if (init() < 0)
	{
		return -1;
	}

	std::clog << "Sending data.\n";
	send(t_socket, data, sizeof(data) - 1, 0);

	return 0;
}

// TODO:文件流传输

tcp_client::~tcp_client()
{
	close(t_socket);
}
}
}
