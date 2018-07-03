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
 * Last Modified:  2018-07-03
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
class ConfigureParser : public an::core::ConfigureINI
{
  public:
    ConfigureParser() : ConfigureINI("/etc/aero-node/configure.ini"){};
    ConfigureParser(const std::string &path) : ConfigureINI(path){};
    ~ConfigureParser(){};
};
#else
class ConfigureParser : public an::core::ConfigureJSON
{
  public:
    ConfigureParser() : ConfigureJSON("/etc/aero-node/configure.json"){};
    ConfigureParser(const std::string &path) : ConfigureJSON(path){};
    ~ConfigureParser(){};
};
#endif

#endif // !_CONFIG_PARSER_H_