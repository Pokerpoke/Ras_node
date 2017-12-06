/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    建立tcp连接并传递数据信息
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-02
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <sys/socket.h>
#include <netinet/in.h>

namespace an
{
namespace core
{
/**
 * @brief TCP客户端
 */
class tcp_client
{
  public:
	tcp_client(const char *dest_ip, int dest_port);
	~tcp_client();

	int send_data(const char *data);
	int send_data(std::string data);
	int is_connected();

  private:
	int t_socket;
	struct sockaddr_in server_addr;
	bool IS_CONNECTED;
	// unsigned int connect_times;

	int init();
};
}
}

#endif // !_TCP_CLIENT_H_
