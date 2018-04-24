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
 * Last Modified:  2017-12-11
 * Modified By:    姜阳 (j824544269@gmail.com)
 *
 * @example  qa_tcp_client.cc
 * 
 */
#include <cstring>
#include <errno.h>

#include "logger.h"
#include "tcp_client.h"

namespace an
{
namespace core
{
/**
 * @brief		构造函数
 *
 * @param[in]   目标IP地址
 * @param[in]   目标端口
 * 
 */
TCPClient::TCPClient(const char *dest_ip,
					 const int dest_port)
	: _dest_ip(dest_ip),
	  _dest_port(dest_port)
{
	memset(&_server_addr, 0, sizeof(_server_addr));

	// 设置协议类型
	_server_addr.sin_family = AF_INET;
	// 设置目标端口
	_server_addr.sin_port = htons(_dest_port);
	// 设置目标IP
	_server_addr.sin_addr.s_addr = inet_addr(_dest_ip);

	_IS_CONNECTED = false;
	_SOCKET_CREATED = false;

	// 创建套接字
	if ((_socket = socket(AF_INET,
						  SOCK_STREAM,
						  IPPROTO_TCP)) < 0)
	{
		_SOCKET_CREATED = false;
		LOG(ERROR) << "Socket creation failed for: "
				   << strerror(errno);
	}
	else
	{
		try_to_connect();
		_SOCKET_CREATED = true;
	}
}

/**
 * @brief 	尝试连接
 *
 * @return  连接状态
 * @retval	0	成功
 * @retval	-1	连接失败
 * 
 */
int TCPClient::try_to_connect()
{
	if ((_err = connect(_socket,
						(struct sockaddr *)&_server_addr,
						sizeof(_server_addr))) < 0)
	{
		_IS_CONNECTED = false;
		LOG(ERROR) << "Connect failed for: "
				   << strerror(errno);
		return -1;
	}
	_IS_CONNECTED = true;
	LOG(INFO) << "Connected to " << _dest_ip << ":" << _dest_port;
	return 0;
}

/**
 * @brief   连接状态
 *
 * 检测连接状态
 *
 * @return	连接状态
 * @retval  true	已连接
 * @retval	false	未连接
 * 
 */
bool TCPClient::is_connected()
{
	return _IS_CONNECTED;
}

/**
 * @brief		发送数据信息
 *
 * @param[in]	input_buffer	输入缓存
 * @return		发送状态
 * @retval		0	发送成功
 * @retval		-1	发送失败，打印错误信息
 * 
 */
int TCPClient::write(const char *input_buffer)
{
	return this->write(input_buffer, sizeof(input_buffer) - 1);
}

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
int TCPClient::write(const char *input_buffer,
					 const int input_buffer_size)
{
	if (!_SOCKET_CREATED)
	{
		return -1;
	}
	if (!_IS_CONNECTED)
	{
		int i;
		// 尝试10次
		while (try_to_connect() < 0)
		{
			if (i++ > 10)
				return -1;
		}
	}

#ifdef ENABLE_DEBUG
	LOG(INFO) << "Sending data...";
#endif

	if (send(_socket,
			 input_buffer,
			 input_buffer_size,
			 0) < 0)
	{
		LOG(ERROR) << "Send failed for: "
				   << strerror(errno);
		return -1;
	}
	else
	{
#ifdef ENABLE_DEBUG
		LOG(INFO) << "Send success.";
#endif
		return 0;
	}
}

/**
 * @brief   析构函数
 * 
 * 关闭套接字
 *
 */
TCPClient::~TCPClient()
{
	close(_socket);
}
}
}
