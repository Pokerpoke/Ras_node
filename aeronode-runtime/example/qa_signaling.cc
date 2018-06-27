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
 * Last Modified:  2018-06-26
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aeronode/signaling.h"
#include "aeronode/logger.h"
#include <string>
#include <cstdio>
#include "gtest/gtest.h"

using namespace std;
using namespace an::core;

int main(int argc, char const *argv[])
{
    logger_init();
    Signaling s;
    s.insert("test-key","test-value");
    LOG(INFO) << s.get("test-key");
    s.set("test-key","test-value-modified");
    LOG(INFO) << s.get("test-key");
    s.remove("test-key");
    LOG(INFO) << s.get("test-key");

    return 0;
}