/**
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author 姜阳
 * @date 2017.07
 * @brief 建立tcp连接并传递数据信息
 * @version 1.0.0
 * 
 */
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

namespace an
{
namespace core
{
class tcp_client
{
public:
	tcp_client();
	~tcp_client();
	int tcp_client_send_data(const char *dest_ip, int dest_port, const char *data);

private:
	int this_socket;

	int tcp_client_init(const char *dest_ip, int dest_port);
};
}
}

#endif
