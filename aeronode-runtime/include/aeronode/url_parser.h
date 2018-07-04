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
#ifndef _URL_PARSER_H_
#define _URL_PARSER_H_

#include <string>
#include <vector>

namespace an
{
namespace core
{
class UrlParser
{
  public:
    UrlParser(const std::string &url);
    UrlParser(){};
    ~UrlParser();

    void parser(const std::string &url);
    std::string get(int _n);
    std::string get_first();
    std::string get_second();
    std::string get_third();

    std::string get_id();
    std::string get_port();
    std::string get_request();
    std::string get_param();

  private:
    std::string _url;
    std::vector<size_t> _splits;
};
} // namespace core
} // namespace an

#endif // !_URL_PARSER_H_