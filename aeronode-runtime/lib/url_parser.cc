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
#include "url_parser.h"
#include "aeronode/logger.h"

namespace an
{
namespace core
{
UrlParser::UrlParser(const std::string &url) : _url(url)
{
    parser(_url);
}

void UrlParser::parser(const std::string &url)
{
    size_t _count = _url.find_first_of("/");
    while (_count != std::string::npos)
    {
        _splits.push_back(_count);
        _count = _url.find_first_of("/", _count + 1);
    }
}

std::string UrlParser::get(int _n)
{
    return _n == 0 ? ("/")
                   : _url.substr(_splits[_n - 1] + 1,
                                 _splits[_n] - _splits[_n - 1] - 1);
}

std::string UrlParser::get_first()
{
    return get(1);
}

std::string UrlParser::get_second()
{
    return get(2);
}

std::string UrlParser::get_third()
{
    return get(3);
}

UrlParser::~UrlParser()
{
}
} // namespace core
} // namespace an