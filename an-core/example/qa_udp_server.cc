/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    UDP服务端例程
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-14
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aero-node/logger.h"
#include "aero-node/udp_server.h"
#include <thread>

using namespace an::core;
using namespace std;

int main()
{
	logger_init();
	int port = 13374;

	UDPServer s(port);

	thread t([&] {
		s.start_listen([&] {
			LOG(INFO) << s.output_buffer;
		});
	});

	LOG(INFO) << "Start listen ...";

	t.join();

	return 0;
}