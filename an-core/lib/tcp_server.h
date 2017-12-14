/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    创建一个TCP服务端，用以接受数据。
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-14
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 * @example	qa_tcp_server_callback.cc
 * @example	qa_tcp_server_override.cc
 * 
 */
#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <netinet/in.h>
#include <sys/socket.h>
#include <functional>

namespace an
{
namespace core
{
/** 
 * @brief	TCP服务端
 * 
 * 创建一个TCP服务端，监听给定的端口。两种方式进行数据处理，
 * 回调函数或者重载。
 * 
 */
class TCPServer
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
	TCPServer(const int server_port);
	/**
	 * @brief	关闭Socket
	 * 
	 */
	~TCPServer();

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
	/// 一次从缓存中读取的大小，默认4096
	long output_buffer_size;

  protected:
	/** 
	 * @brief	负载处理函数
	 * 
	 */
	virtual void payload_process(){};
	/**
	 * @brief	tcp服务器初始化
	 * 
	 * @return	初始化结果
	 * @retval	0	初始化成功
	 * @retval	-1	Socket创建失败
	 * @retval	-2	Socket绑定失败
	 * @retval	-3	Socket监听失败
	 * 
	 */
	int init();

  private:
	/// 服务端口
	int _server_port;
	/// 监听套接字
	int _listen_socket;
	/// 连接套接字
	int _conn_socket;
	/// 错误处理
	int _err;
	/// 缓冲区长度
	int _backlog;
	/// 地址长度，accept()用
	int _addrlen;

	/// 标志位
	/// 套接字创建成功
	bool _SOCKET_CREATED;
	/// 监听套接字关闭
	bool _LISTEN_SOCKET_CLOSED;
	/// 连接套接字关闭
	bool _CONN_SOCKET_CLOSED;

	/// socket地址
	/// 服务端
	struct sockaddr_in _server_addr;
	/// 客户端信息
	struct sockaddr_in _client_addr;

	/** 
	 * @brief	等待连接
	 * 
	 * @return  连接状态
	 * @retval	true	已连接
	 * @retval	false	未连接
	 * 
	 */
	bool connected();
};
}
}

#endif // !_TCP_SERVER_H_