/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file      udp_client.h
 * @author    姜阳
 * @date      2017.07
 * @brief     udp客户端
 * @version   1.0.0
 * 
 */

#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_

#include <netinet/in.h>
#include <sys/socket.h>

namespace an
{
namespace core
{
class udp_client
{
  public:
	udp_client(const char *dest_ip, int dest_port);
	~udp_client();
	int send_data(const char *data);

  private:
	int t_socket;
	struct sockaddr_in server_addr;

	int init();
};
}
}

#endif // !_UDP_CLIENT_H_