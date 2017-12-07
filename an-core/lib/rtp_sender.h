/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    RTP发送类
 * @version  0.0.1
 * @example  qa_rtp_sender.cc
 * 
 * Last Modified:  2017-12-07
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#ifndef _RTP_SENDER_H_
#define _RTP_SENDER_H_

#include <rtpsession.h>
#include <rtpudpv4transmitter.h>
#include <rtpipv4address.h>
#include <rtpsessionparams.h>
#include <rtperrors.h>
#include <rtplibraryversion.h>
#include <rtppacket.h>
#include <stdlib.h>
#include <string>

namespace an
{
namespace core
{
/** 
 * @brief   RTP发送类
 * 
 * 发送至目标地址的相应端口
 * 
 */
class RTPSender
{
  public:
	/** 
	 * @brief   RTPSender构造函数
	 * 
	 * 发送至目标地址的相应端口
	 * 
	 * @param   [in]   ip    目标地址
	 * @param   [in]   port  目标端口
	 * 
	 */
	RTPSender(const std::string ip,
			  const int port = 13374);
	/** 
	 * @brief   RTPSender析构函数
	 * 
	 * 断开RTP传输
	 * 
	 */
	~RTPSender();

	/** 
	 * @brief   RTP发送
	 * 
	 * RTP发送函数，失败打印错误信息
	 * 
	 * @param   [in]  input_buffer  待写入缓存
	 * @param	[in]  input_buffer_size  待写入缓存大小
	 * 
	 * @retval  -1  发送失败
	 * @retval   0  发送成功
	 * 
	 */
	int write(const char *input_bufffer,
			  const int input_buffer_size);

	/// 目标地址，使用string方便进行转换
	std::string dest_ip;
	/// 目标端口
	int dest_port;
	// 本地端口，可以不用设置
	// int host_port;
	/// 负载数据类型
	int payload_type;
	/// 时间戳
	double time_stamp;
	/// 是否填充
	bool mark;

  private:
	/** 
	 * @brief   RTP初始化
	 * 
	 * 设置RTP的传输参数，会话参数，并创建RTP会话
	 * 
	 */
	int init();

	/// RTP会话
	jrtplib::RTPSession session;
	/// IPv4传输参数
	jrtplib::RTPUDPv4TransmissionParams transparams;
	/// 会话参数
	jrtplib::RTPSessionParams sessionparams;

	/// 用于判断错误
	int err;
};
}
}

#endif // !_RTP_SENDER_H_