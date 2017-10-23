/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author    姜阳
 * @date      2017.07
 * @brief     UDP服务端
 * @version   0.0.1
 * 
 */

#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace an
{
namespace core
{
/**
 * @brief	UDP服务端
 * 
 */
class udp_server
{
  public:
	udp_server(int server_port);
	~udp_server();

	int udp_listen(char *out, int len);

  private:
	int t_socket;
	socklen_t t_len;

	struct sockaddr_in server_addr;

	int init();
};
}
}

#endif // !_UDP_SERVER_H_