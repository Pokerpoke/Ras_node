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

#include <string>
#include "aeronode/logger.h"
#include "aeronode/path_parser.h"

using namespace std;
using namespace an::core;

int main(int argc, char const *argv[])
{
    logger_init();

    string path = "/test1/test2/test3/";

    PathParser p(path);
    LOG(INFO) << p.get(0);
    LOG(INFO) << p.get_first();
    LOG(INFO) << p.get_second();
    LOG(INFO) << p.get_third();

    getchar();
    return 0;
}
