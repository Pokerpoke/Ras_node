################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-06
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-06-30
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

# 设置目标系统
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 设置工具链目录
set(TOOLS_CHAIN_DIR 
    /usr/arm-linux-gnueabi
    )
set(QT_EMBEDDED_DIR
    /usr/local/Trolltech/QtEmbedded-4.8.5-arm
    )
set(TOOLS_CHAIN_INCLUDE 
    ${TOOLS_CHAIN_DIR}/include
    ${QT_EMBEDDED_DIR}/include
    )
set(TOOLS_CHAIN_LIB 
    ${TOOLS_CHAIN_DIR}/lib
    ${QT_EMBEDDED_DIR}/lib
    )

# 设置编译器位置
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")

# 设置Cmake查找主路径
set(CMAKE_FIND_ROOT_PATH 
    ${TOOLS_CHAIN_DIR}
    ${QT_EMBEDDED_DIR}
    )

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# 只在指定目录下查找库文件
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# 只在指定目录下查找头文件
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# 只在指定目录下查找依赖包
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

include_directories(
    ${TOOLS_CHAIN_DIR}/include
    ${QT_EMBEDDED_DIR}/include
    )

set(CMAKE_INCLUDE_PATH 
    ${TOOLS_CHAIN_INCLUDE}
    )

set(CMAKE_LIBRARY_PATH 
    ${TOOLS_CHAIN_LIB}
    )

# set(CMAKE_PREFIX_PATH ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi)