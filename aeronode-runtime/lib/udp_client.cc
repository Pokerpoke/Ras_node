/**
 *
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 *
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    UDP客户端
 * @version  0.0.1
 *
 * Last Modified:  2018-06-25
 * Modified By:    姜阳 (j824544269@gmail.com)
 *
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>

#include "logger.h"
#include "udp_client.h"

namespace an
{
namespace core
{
/** 
 * @brief   构造函数
 * 
 * 初始化相关变量
 * 
 * @param[in]	dest_ip		目标地址
 * @param[in]	dest_port	目标端口
 * 
 */
UDPClient::UDPClient(const char *dest_ip, const int dest_port)
    : _dest_ip(dest_ip), _dest_port(dest_port)
{
    std::memset(&_server_addr, 0, sizeof(_server_addr));

    // 设置协议类型
    _server_addr.sin_family = AF_INET;
    // 设置目标端口
    _server_addr.sin_port = htons(_dest_port);
    // 设置目标IP
    _server_addr.sin_addr.s_addr = inet_addr(_dest_ip);

    _SOCKET_CREATED = false;

    init();
}

/** 
 * @brief   初始化函数
 * 
 * 创建套接字
 * 
 * @retval  0    成功
 * @retval  -1   失败
 * 
 */
int UDPClient::init()
{
    _SOCKET_CREATED = false;
    // 设置传输模式
    if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        LOG(ERROR) << "Socket create failed.";
        return -1;
    }
    _SOCKET_CREATED = true;
    return 0;
}

/** 
 * @brief   发送数据
 * 
 * @param[in]    input_buffer	输入缓存
 * @return	发送成功返回发送的数据长度
 * @retval  -1    发送失败
 * 
 */
int UDPClient::write(const char *input_buffer)
{
    return write(input_buffer, sizeof(input_buffer));
}

/** 
 * @brief   发送数据
 * 
 * @param[in]    input_buffer	输入缓存
 * @param[in]    input_buffer_size	输入缓存大小
 * @return	发送成功返回发送的数据长度
 * @retval  -1    发送失败
 * 
 */
int UDPClient::write(const char *input_buffer, const int input_buffer_size)
{

#ifdef ENABLE_DEBUG
    LOG(INFO) << "Sending data ...";
#endif

    if ((_err = sendto(_socket,                          // Socket
                       input_buffer,                     // 发送信息
                       input_buffer_size,                // 信息大小
                       0,                                // 标志位
                       (struct sockaddr *)&_server_addr, // 接收端地址
                       sizeof(_server_addr))) < 0)       // 接收端地址大小
    {
        LOG(ERROR) << "Send data failed for: "
                   << strerror(errno);
        return -1;
    }
    return _err;
}

/** 
 * @brief   析构函数
 * 
 * 关闭socket
 * 
 */
UDPClient::~UDPClient()
{
    close(_socket);
}
} // namespace core
} // namespace an