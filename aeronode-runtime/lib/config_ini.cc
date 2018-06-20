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

#include <cstddef>
#include "aeronode/logger.h"

#include "config_ini.h"

namespace an
{
namespace core
{
ConfigureINI::ConfigureINI(const std::string &configure_path)
{
    _config = new INIReader(configure_path);
}

std::string ConfigureINI::get(const std::string &section,
                              const std::string &key,
                              const std::string &default_value)
{
    return _config->Get(section, key, default_value);
}

int ConfigureINI::get_integer(const std::string &section,
                              const std::string &key,
                              const int &default_value)
{
    return _config->GetInteger(section, key, default_value);
}

std::string ConfigureINI::get_string(const std::string &section,
                                     const std::string &key,
                                     const std::string &default_value)
{
    return _config->Get(section, key, default_value);
}

bool ConfigureINI::get_bool(const std::string &section,
                            const std::string &key,
                            const bool &default_value)
{
    return _config->GetBoolean(section, key, default_value);
}

double ConfigureINI::get_double(const std::string &section,
                                const std::string &key,
                                const double &default_value)
{
    return _config->GetReal(section, key, default_value);
}

ConfigureINI::~ConfigureINI()
{
    delete _config;
}
} // namespace core
} // namespace an