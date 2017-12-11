/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    
 * @version  0.0.2
 * 
 * Last Modified:  2017-12-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "system_info.h"
#include "logger.h"

#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace an
{
namespace core
{
SystemInfo::SystemInfo()
{
	update();
};
SystemInfo::~SystemInfo(){

};
int SystemInfo::update()
{
	if ((err = get_os_info()) < 0)
	{
		LOG(ERROR) << "Get os info error.";
		return -1;
	}
	if ((err = get_mem_info()) < 0)
	{
		LOG(ERROR) << "Get mem info error.";
		return -1;
	}
	if ((err = get_ip_info()) < 0)
	{
		LOG(ERROR) << "Get ip info error.";
		return -1;
	}
	return 0;
}
int SystemInfo::get_os_info()
{
	return uname(&os_info);
}
int SystemInfo::get_mem_info()
{
	return sysinfo(&mem_info);
}
int SystemInfo::get_ip_info()
{
	/// [get-the-ip-address-of-the-machine)](https://stackoverflow.com/questions/212528/get-the-ip-address-of-the-machine)
	struct ifaddrs *ifAddrStruct = NULL;
	struct ifaddrs *ifa = NULL;
	void *tmpAddrPtr = NULL;

	if (getifaddrs(&ifAddrStruct) < 0)
		return -1;

	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (!ifa->ifa_addr)
		{
			continue;
		}
		if (ifa->ifa_addr->sa_family == AF_INET)
		{ // check it is IP4
			// is a valid IP4 Address
			tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			// printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
			ip_info[static_cast<std::string>(ifa->ifa_name)] = static_cast<std::string>(addressBuffer);
		}
		// else if (ifa->ifa_addr->sa_family == AF_INET6)
		// { // check it is IP6
		// 	// is a valid IP6 Address
		// 	tmpAddrPtr = &((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
		// 	char addressBuffer[INET6_ADDRSTRLEN];
		// 	inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
		// 	printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
		// }
	}
	if (ifAddrStruct != NULL)
		freeifaddrs(ifAddrStruct);
	return 0;
}
}
}