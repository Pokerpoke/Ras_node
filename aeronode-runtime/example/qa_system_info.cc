/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-04-24
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aeronode/system_info.h"
#include "aeronode/logger.h"
using namespace std;
using namespace an::core;
int main()
{
    logger_init();

    SystemInfo s;
    s.update();
    LOG(INFO) << "Print os info";
    LOG(INFO) << s.os_info.sysname;
    LOG(INFO) << s.os_info.nodename;
    LOG(INFO) << s.os_info.release;
    // LOG(INFO) << s.os_info.version;
    LOG(INFO) << s.os_info.machine;

    LOG(INFO) << "Print mem info";
    // s.mem_info.totalram / 1024 / 1024 -> s.mem_info.totalram >> 20
    LOG(INFO) << "Total : "
              << (s.mem_info.totalram >> 20)
              << " MB";
    LOG(INFO) << "Free : "
              << (s.mem_info.freeram >> 20)
              << " MB";
    LOG(INFO) << "Free ram : "
              << (double)(s.mem_info.freeram >> 20) /
                     (double)(s.mem_info.totalram >> 20) * 100
              << "%";

    LOG(INFO) << "Print ip info";
    // Tiny4412 don't support the follow syntax, 😢
    // for (auto i : s.ip_info)
    map<string, string>::iterator i;
    for (i = s.ip_info.begin(); i != s.ip_info.end(); i++)
    {
        LOG(INFO) << i->first
                  << " : " << i->second;
    }

    getchar();
    return 0;
}