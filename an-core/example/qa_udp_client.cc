/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    UDP客户端例程
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-14
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aero-node/udp_client.h"
#include "aero-node/logger.h"

using namespace an::core;

int main()
{
	logger_init();

	UDPClient c("127.0.0.1", 13374);
	for (int i = 0; i < 10; i++)
	{
		c.write("123\n", 4);
	}

	getchar();
	return 0;
}