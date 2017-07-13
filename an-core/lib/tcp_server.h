/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file    : tcp_server.h
 * @author  : 姜阳
 * @date    : 2017.07
 * @brief   : 创建一个tcp服务端，用以接受数据。
 * @version : 1.0.0
 * 
 */

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <netinet/in.h>
#include <sys/socket.h>

namespace an
{
namespace core
{
/**
 * @brief TCP服务端
 */
class tcp_server
{
public:
	tcp_server(int server_port);
	~tcp_server();
	int tcp_listen(char *out);

private:
	int tcp_server_init(int server_port);
	int listen_socket, conn_socket;
	struct sockaddr_in server_addr;
};
}
}

#endif