/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    建立tcp连接并传递数据信息
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-12
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 * @example  qa_tcp_client.cc
 * 
 */
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace an
{
namespace core
{
/**
 * @brief	TCP客户端
 * @todo	心跳保持连接
 * 
 */
class TCPClient
{
  public:
	/**
	 * @brief		构造函数
	 *
	 * @param[in]   dest_ip		目标IP地址
	 * @param[in]   dest_port	目标端口
	 *
	 */
	TCPClient(const char *dest_ip,
			  const int dest_port);

	/**
	 * @brief   析构函数
	 * 
	 * 关闭套接字
	 *
	 */
	~TCPClient();

	/**
	 * @brief		发送数据信息
	 *
	 * @param[in]	input_buffer	输入缓存
	 * @return		发送状态
	 * @retval		0	发送成功
	 * @retval		-1	发送失败，打印错误信息
	 * 
	 */
	int write(const char *input_buffer);
	/**
	 * @brief		发送数据信息
	 *
	 * @param[in]	input_buffer		输入缓存
	 * @param[in]	input_buffer_size	输入缓存大小
	 * @return		发送状态
	 * @retval		0	发送成功
	 * @retval		-1	发送失败，打印错误信息
	 * 
	 */
	int write(const char *input_buffer,
			  const int input_buffer_size);

	/**
	 * @brief   连接状态
	 *
	 * 检测连接状态
	 *
	 * @retval  true	已连接
	 * @retval	false	未连接
	 *
	 */
	bool is_connected();

  private:
	/**
	 * @brief 	尝试连接
	 *
	 * @return  连接状态
	 * @retval	0	成功
	 * @retval	-1	连接失败
	 *
	 */
	int try_to_connect();

	/// 套接字
	int _socket;
	/// 错误代码
	int _err;
	/// 目标ip
	const char *_dest_ip;
	/// 目标端口
	const int _dest_port;
	/// 服务端地址
	struct sockaddr_in _server_addr;
	/// 是否连接
	bool _IS_CONNECTED;
	/// 用以检测套接字创建是否成功
	bool _SOCKET_CREATED;
};
}
}

#endif // !_TCP_CLIENT_H_