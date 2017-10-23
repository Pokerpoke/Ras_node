/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author    姜阳
 * @date      2017.07
 * @brief     创建一个UDP服务端
 * @version   0.0.1
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
#include <vector>

#include "udp_server.h"

namespace an
{
namespace core
{

/**
 * @param[in]   server_port		监听端口
 * 
 */
udp_server::udp_server(int server_port)
{
	std::memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	t_len = sizeof(server_addr);

	init();
}

/**
 * UDP服务端初始化
 * 
 * @param   NULL
 * @return  0,-1,-2
 * @retval	0	正常结束
 * @retval	-1	Socket创建失败
 * @retval	-2	Socket绑定失败
 * 
 */
int udp_server::init()
{
	if ((t_socket = socket(AF_INET,
						   SOCK_DGRAM,
						   IPPROTO_UDP)) < 0)
	{
		std::cerr << "Socket create failed\n";
		return -1;
	}

	if (bind(t_socket,
			 (struct sockaddr *)&server_addr,
			 sizeof(server_addr)) < 0)
	{
		std::cerr << "Socket bind failed\n";
		return -2;
	}
	return 0;
}

/**
 * 开始监听端口
 * 
 * @param[in,out]		out		输出数组
 * @param[in]			len		数组长度
 * @return  			成功返回0，失败返回-1
 * @warning				调用之后首先将输出数组置零！
 * @retval				0	接受成功
 * @retval				-1	初始化失败
 * 
 */
int udp_server::udp_listen(char *out, int len)
{
	memset(out, 0, len);
	if (recvfrom(t_socket,
				 out,
				 len,
				 0,
				 (struct sockaddr *)&server_addr,
				 &t_len) < 0)
	{
		std::cerr << "Receive failed\n";
		return -1;
	}
	return 0;
}

udp_server::~udp_server()
{
	close(t_socket);
}
}
}
