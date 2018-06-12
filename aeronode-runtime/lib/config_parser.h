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
#ifndef _CONFIG_PARSER_H_
#define _CONFIG_PARSER_H_

#include <string>
#include "aeronode/config.h"
#ifdef AN_TARGET_TINY4412
#include "aeronode/config_ini.h"
#else
#include "aeronode/config_json.h"
#endif

#ifdef AN_TARGET_TINY4412
// ConfigureINI ANConfigure("/etc/aeronode/configure.ini");

an::core::ConfigureINI ANConfigure("/home/jiang/git/aero-node/aeronode-runtime/lib/configure.ini");
#else
// ConfigureJSON ANConfigure("/etc/aeronode/configure.json");

an::core::ConfigureJSON ANConfigure("/home/jiang/git/aero-node/aeronode-runtime/lib/configure.json");
#endif

#endif // !_CONFIG_PARSER_H_