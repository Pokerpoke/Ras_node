/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    tcp服务端例程2，继承类形式
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-11
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <iostream>

#include "an-core/logger.h"
#include "an-core/tcp_server.h"

class TCPServer : public an::core::TCPServer
{
  public:
	TCPServer(const int server_port) : an::core::TCPServer(server_port)
	{
	}

  protected:
	void payload_process()
	{
		LOG(INFO) << output_buffer;
	}
};

int main()
{
	logger_init();

	TCPServer s(13374);
	s.start_listen();

	return 0;
}