# 设置目标系统
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 设置工具链目录
set(TOOL_CHAIN_DIR /opt/FriendlyARM/toolschain/4.5.1)
set(TOOL_CHAIN_INCLUDE 
	${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/sys-root/usr/include
    ${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/include
	)
set(TOOL_CHAIN_LIB 
	${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/sys-root/usr/lib
    ${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/include
	)

# 设置编译器位置
set(CMAKE_C_COMPILER "arm-linux-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-g++")

# 设置Cmake查找主路径
set(CMAKE_FIND_ROOT_PATH ${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# 只在指定目录下查找库文件
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# 只在指定目录下查找头文件
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# 只在指定目录下查找依赖包
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

include_directories(
	${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/include
	${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/sys-root/usr/include
	)

# link_directories(
# 	${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/lib
# 	${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi/sys-root/usr/lib
# 	)

set(CMAKE_INCLUDE_PATH 
	${TOOL_CHAIN_INCLUDE}
	)

set(CMAKE_LIBRARY_PATH 
	${TOOL_CHAIN_LIB}
	)

# set(CMAKE_PREFIX_PATH ${TOOL_CHAIN_DIR}/arm-none-linux-gnueabi)