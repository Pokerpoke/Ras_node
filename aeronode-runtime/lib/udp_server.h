/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    创建一个UDP服务端
 * @version  0.0.1
 * 
 * Last Modified:  2018-06-25
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 * @example	qa_udp_server.cc
 * 
 */
#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>

namespace an
{
namespace core
{
/**
 * @brief	UDP服务端
 * 
 */
class UDPServer
{
  public:
    /** 
	 * @brief   构造函数
	 * 
	 * 初始化相关变量
	 * 
	 * @param[in]   server_port	监听端口
	 * 
	 */
    UDPServer(const int server_port);
    /**
	 * @brief	析构函数
	 * 
	 * 关闭Socket
	 * 
	 */
    ~UDPServer();

    /** 
	 * @brief   开始监听
	 * 
	 * 通过继承该类，并重载payload_process函数进行监听
	 * 
	 */
    int start_listen();
    /** 
	 * @brief   开始监听
	 * 
	 * 回调函数方式，传入函数指针或者lambda函数
	 * 
	 * @param[in]	_payload_process	数据处理函数
	 * 
	 */
    int start_listen(std::function<void(void)> _payload_process);

    /// 输出缓存
    char *output_buffer;
    /// 输出缓存大小
    int output_buffer_size;

  private:
    /** 
	 * @brief	初始化
	 * 
	 * @return  0,-1,-2
	 * @retval	0	正常结束
	 * @retval	-1	Socket创建失败
	 * @retval	-2	Socket绑定失败
	 * 
	 */
    int init();
    /** 
	 * @brief	负载处理函数
	 * 
	 */
    virtual void payload_process(){};

  private:
    /// 套接字
    int _socket;
    /// 监听端口
    int _server_port;
    /// 错误代码
    int _err;
    /// 套接字长度
    socklen_t _len;

    /// 地址结构体
    struct sockaddr_in _server_addr;

    /// 标志位
    bool _SOCKET_CREATED;
};
} // namespace core
} // namespace an

#endif // !_UDP_SERVER_H_