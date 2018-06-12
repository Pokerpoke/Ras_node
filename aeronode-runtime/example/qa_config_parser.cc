/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-06
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-06-12
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aeronode/config.h"
#include "aeronode/logger.h"
#include "aeronode/config_ini.h"

#ifndef AN_TARGET_TINY4412
#include "aeronode/config_json.h"
#endif // !AN_TARGET_TINY4412

using namespace an::core;

int main(int argc, char const *argv[])
{
    logger_init();

    ConfigureINI c_ini("/home/jiang/git/aero-node/aeronode-runtime/lib/configure.ini");

    LOG(INFO) << c_ini.get_string("server", "ip", "192.168.0.1");
    LOG(INFO) << c_ini.get_integer("server", "listen_port", 8336);

#ifndef AN_TARGET_TINY4412
    ConfigureJSON c_json("/home/jiang/git/aero-node/aeronode-runtime/lib/configure.json");

    LOG(INFO) << c_json.get_string("video", "codec", "UNKNOWN");
    LOG(INFO) << c_json.get_integer("video", "height", 400);
#endif // !AN_TARGET_TINY4412

    getchar();

    return 0;
}
