# 设置目标系统
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 设置工具链目录
set(TOOLS_CHAIN_DIR 
    /opt/FriendlyARM/toolschain/4.5.1
    )
set(QT_EMBEDDED_DIR
    /usr/local/Trolltech/QtEmbedded-4.8.5-arm
    )
set(TOOLS_CHAIN_INCLUDE 
    ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi/sys-root/usr/include
    ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi/include
    ${QT_EMBEDDED_DIR}/include
    )
set(TOOLS_CHAIN_LIB 
    ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi/sys-root/usr/lib
    ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi/lib
    ${QT_EMBEDDED_DIR}/lib
    )

# 设置编译器位置
set(CMAKE_C_COMPILER "arm-linux-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-g++")

# 设置Cmake查找主路径
set(CMAKE_FIND_ROOT_PATH 
    ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi
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
    ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi/include
    ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi/sys-root/usr/include
    ${QT_EMBEDDED_DIR}/include
    )

set(CMAKE_INCLUDE_PATH 
    ${TOOLS_CHAIN_INCLUDE}
    )

set(CMAKE_LIBRARY_PATH 
    ${TOOLS_CHAIN_LIB}
    )

# set(CMAKE_PREFIX_PATH ${TOOLS_CHAIN_DIR}/arm-none-linux-gnueabi)