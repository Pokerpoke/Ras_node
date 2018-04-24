/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    tcp服务端例程1，回调函数形式
 * @version  0.0.1
 * 
 * Last Modified:  2018-04-24
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aeronode/logger.h"
#include "aeronode/tcp_server.h"

using namespace an::core;

void foo(void)
{
	LOG(INFO) << "test";
}

int main()
{
	logger_init();

	TCPServer s(13374);
	// 传入lambda函数
	s.start_listen([&] {
		LOG(INFO) << s.output_buffer;
	});
	// 传入普通函数
	// s.start_listen(foo);

	return 0;
}