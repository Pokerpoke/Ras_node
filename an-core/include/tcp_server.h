/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
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
#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <netinet/in.h>
#include <sys/socket.h>

namespace an
{
namespace core
{
/** 
 * @brief	TCP服务端
 * 
 * 创建一个TCP服务端，监听给定的端口。
 * 
 */
class tcp_server
{
  public:
	tcp_server(int server_port);
	~tcp_server();

	int tcp_receive(char *out, int len);
	int is_connected();
	int close_connect();

  private:
	int listen_socket;
	int conn_socket;

	bool LISTEN_SOCKET_IS_CLOSED;
	bool CONN_SOCKET_IS_CLOSED;

	struct sockaddr_in server_addr;

	int init();
};
}
}

#endif