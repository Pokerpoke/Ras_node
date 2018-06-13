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
 * Last Modified:  2018-06-13
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <iostream>
#include <sstream>
#include "aeronode/config_json.h"

namespace an
{
namespace core
{
ConfigureJSON::ConfigureJSON(const std::string &config_path)
{
    _config_file = new std::ifstream(config_path);
    std::stringstream _temp;
    _temp << _config_file->rdbuf();
    _config = new nlohmann::json();
    *_config = nlohmann::json::parse(_temp.str());
}

std::string ConfigureJSON::get(const std::string &section,
                               const std::string &key,
                               const std::string &default_value) const
{
    return _config->at(section).at(key).is_string() ? _config->at(section).at(key).dump()
                                                    : default_value;
}

std::string ConfigureJSON::get_string(const std::string &section,
                                      const std::string &key,
                                      const std::string &default_value) const
{
    return _config->at(section).at(key).is_string() ? _config->at(section).at(key).get<std::string>()
                                                    : default_value;
}

int ConfigureJSON::get_integer(const std::string &section,
                               const std::string &key,
                               const int &default_value) const
{
    return _config->at(section).at(key).is_number() ? _config->at(section).at(key).get<int>()
                                                    : default_value;
}

double ConfigureJSON::get_double(const std::string &section,
                                 const std::string &key,
                                 const double &default_value) const
{
    return _config->at(section).at(key).is_number() ? _config->at(section).at(key).get<double>()
                                                    : default_value;
}

ConfigureJSON::~ConfigureJSON()
{
    delete _config_file;
    delete _config;
}
} // namespace core
} // namespace an