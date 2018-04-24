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
 * Last Modified:  2017-12-14
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 * @example	qa_udp_client.cc
 * 
 */
#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_

#include <netinet/in.h>
#include <sys/socket.h>

namespace an
{
namespace core
{
/**
 * @brief	UDP客户端
 */
class UDPClient
{
  public:
	/** 
	 * @brief   构造函数
	 * 
	 * 初始化相关变量
	 * 
	 * @param[in]	dest_ip		目标地址
	 * @param[in]	dest_port	目标端口
	 * 
	 */
	UDPClient(const char *dest_ip, const int dest_port);
	/** 
	 * @brief   析构函数
	 * 
	 * 关闭socket
	 * 
	 */
	~UDPClient();

	/** 
	 * @brief   发送数据
	 * 
	 * @param[in]    input_buffer	输入缓存
	 * @return	发送成功返回发送的数据长度
	 * @retval  -1    发送失败
	 * 
	 */
	int write(const char *input_buffer);
	/** 
	 * @brief   发送数据
	 * 
	 * @param[in]    input_buffer	输入缓存
	 * @param[in]    input_buffer_size	输入缓存大小
	 * @return	发送成功返回发送的数据长度
	 * @retval  -1    发送失败
	 * 
	 */
	int write(const char *input_buffer, const int input_buffer_size);

  protected:
	/** 
   * @brief   初始化函数
   * 
   * 创建套接字
   * 
   * @retval  0    成功
   * @retval  -1   失败
   * 
   */
	int init();

  private:
	/// 目标地址
	const char *_dest_ip;
	/// 目标端口
	const int _dest_port;
	/// 套接字
	int _socket;
	/// 错误代码
	int _err;
	/// 地址结构体
	struct sockaddr_in _server_addr;

	/// 标志位
	bool _SOCKET_CREATED;
};
}
}

#endif // !_UDP_CLIENT_H_