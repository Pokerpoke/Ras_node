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
#ifndef _CONFIG_JSON_H_
#define _CONFIG_JSON_H_

#include "aeronode/config.h"

#include <string>
#include <fstream>

#include "json.h"

namespace an
{
namespace core
{
class ConfigureJSON
{
  public:
    ConfigureJSON(const std::string &config_path);
    ~ConfigureJSON();

    std::string get(const std::string &section,
                    const std::string &key,
                    const std::string &default_value) const;
    std::string get_string(const std::string &section,
                           const std::string &key,
                           const std::string &default_value) const;
    int get_integer(const std::string &section,
                    const std::string &key,
                    const int &default_value) const;
    double get_double(const std::string &section,
                      const std::string &key,
                      const double &default_value) const;

  private:
    nlohmann::json *_config;
    std::ifstream *_config_file;
};
} // namespace core
} // namespace an

#endif // !_CONFIG_JSON_H_