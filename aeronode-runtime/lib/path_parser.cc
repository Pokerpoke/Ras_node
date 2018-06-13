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
#include "path_parser.h"
#include "aeronode/logger.h"

namespace an
{
namespace core
{
PathParser::PathParser(const std::string &path) : _path(path)
{
    size_t _count = _path.find_first_of("/");
    while (_count != std::string::npos)
    {
        _splits.push_back(_count);
        _count = _path.find_first_of("/", _count + 1);
    }
}

std::string PathParser::get(int _n)
{
    return _n == 0 ? ("/")
                   : _path.substr(_splits[_n - 1] + 1,
                                  _splits[_n] - _splits[_n - 1] - 1);
}

std::string PathParser::get_first()
{
    return get(1);
}

std::string PathParser::get_second()
{
    return get(2);
}

std::string PathParser::get_third()
{
    return get(3);
}

PathParser::~PathParser()
{
}
} // namespace core
} // namespace an