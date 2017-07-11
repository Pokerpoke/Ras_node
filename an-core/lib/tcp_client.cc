/**
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author 姜阳
 * @date 2017.07
 * @brief 建立tcp连接并传递数据信息
 * @version 1.0.0
 * 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "tcp_client.h"

namespace an
{
namespace core
{

tcp_client::tcp_client()
{
}

/**
 * 初始化tcp连接
 * @param socked字
 * @param 目标地址
 * @param 目标ip
 * @return 成功返回0，socket创建失败返回-1，连接失败返回-2
 */
int tcp_client::tcp_client_init( const char *dest_ip, int dest_port)
{
	struct sockaddr_in dest;

	dest.sin_family = AF_INET;
	//设置传输模式
	this_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this_socket < 0)
	{
		fprintf(stderr, "Socket creation failed.");
		return -1;
	}

	//设置目标端口
	dest.sin_port = htons(dest_port);
	//设置目标IP
	dest.sin_addr.s_addr = inet_addr(dest_ip);
	if (connect(this_socket, (struct sockaddr *)&dest, sizeof(dest)) != 0)
	{
		fprintf(stderr, "Connected failed.");
		if (this_socket)
			close(this_socket);
		return -2;
	}
	fprintf(stderr, "Connected.");

	return 0;
}

/**
 * 发送数据信息
 * @param 目标ip
 * @param 目标端口
 * @param char类型的数据信息
 * @return 成功返回0
 */
int tcp_client::tcp_client_send_data(const char *dest_ip, int dest_port, const char *data)
{

	tcp_client_init( dest_ip, dest_port);

	send(this_socket, data, sizeof(data) - 1, 0);

	return 0;
}

// TODO:文件流传输

tcp_client::~tcp_client()
{
	close(this_socket);
}
}
}
