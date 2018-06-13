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
#ifndef _PATH_PARSER_H_
#define _PATH_PARSER_H_

#include <string>
#include <vector>

namespace an
{
namespace core
{
class PathParser
{
  public:
    PathParser(const std::string &path);
    ~PathParser();

    std::string get(int _n);
    std::string get_first();
    std::string get_second();
    std::string get_third();

  private:
    std::string _path;
    std::vector<size_t> _splits;
};
} // namespace core
} // namespace an

#endif // !_PATH_PARSER_H_