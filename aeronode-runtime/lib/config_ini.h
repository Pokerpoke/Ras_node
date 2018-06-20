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

#ifndef _INI_CONFIG_H_
#define _INI_CONFIG_H_

#include <string>

#include "aeronode/ini_reader.h"

namespace an
{
namespace core
{
class ConfigureINI
{
  public:
    ConfigureINI(const std::string &path);
    ~ConfigureINI();
    std::string get(const std::string &section,
                    const std::string &key,
                    const std::string &default_value);
    int get_integer(const std::string &section,
                    const std::string &key,
                    const int &default_value);
    bool get_bool(const std::string &section,
                  const std::string &key,
                  const bool &default_value);
    std::string get_string(const std::string &section,
                           const std::string &key,
                           const std::string &default_value);
    double get_double(const std::string &section,
                      const std::string &key,
                      const double &default_value);

  private:
    INIReader *_config;
};
} // namespace core
} // namespace an

#endif // !_INI_CONFIG_H_