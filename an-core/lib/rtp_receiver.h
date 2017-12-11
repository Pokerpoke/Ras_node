/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    RTP接收类
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 * @example  qa_rtp_receiver.cc
 * @example  qa_rtp_sender_to_receiver.cc
 * 
 */
#ifndef _RTP_RECEIVER_H_
#define _RTP_RECEIVER_H_

#include <rtpsession.h>
#include <rtpudpv4transmitter.h>
#include <rtpipv4address.h>
#include <rtpsessionparams.h>
#include <rtperrors.h>
#include <rtplibraryversion.h>
#include <rtppacket.h>
#include <stdlib.h>

#include "logger.h"

namespace an
{
namespace core
{
/**
 * @brief   RTP接收类
 * 
 * @note    使用了一个while(1)循环进行数据处理，提供了payload_process()
 * 的纯虚函数用以进行负载数据处理，请继承该类并实现该函数以进行数
 * 据处理。参考例程以获得更多信息。
 * 
 */
class RTPReceiver
{
public:
  /** 
     * @brief   RTPReceiver构造函数
     * 
     * 构造函数，初始化相关配置。
     * 
     * @param   [in]   _portbase  监听端口，默认是8338
     * 
     */
  RTPReceiver(const int _portbase = 8338);
  /** 
     * @brief   RTPReceiver析构函数
     * 
     */
  virtual ~RTPReceiver();

  /** 
     * @brief   开始监听
     * 
     * 使用了一个while(1)循环进行数据处理，提供了payload_process()
     * 的纯虚函数用以进行负载数据处理，请继承该类并实现该函数以进行数
     * 据处理。
     * 
     * @retval  0   成功
     * @retval  -1  处理过程出现了错误，查看log以获取详细信息
     * 
     */
  int start_listen();

  /// 输出缓存
  char *output_buffer;
  /// 输出缓存大小
  uint32_t output_buffer_size;

  /// 时间戳
  double time_stamp;
  /// 负载类型，查看[RFC3551](https://www.iana.org/assignments/rtp-parameters/rtp-parameters.xhtml)
  int payload_type;
  /// 监听端口
  int portbase;
  /// 是否填充
  bool mark;

protected:
  /** 
     * @brief   负载处理函数
     * 
     * 重新实现该成员函数以进行负载数据处理
     * 
     */
  virtual void payload_process() = 0;
  /// jrtp收到的包
  jrtplib::RTPPacket *output_packet;

private:
  /** 
     * @brief   初始化函数
     * 
     * 进行相关初始化
     * 
     * @param   [in]   
     * @retval  0      成功
     * @retval  -1     失败
     * 
     */
  int init();

  /// jrtp会话
  jrtplib::RTPSession session;
  /// 传输参数
  jrtplib::RTPUDPv4TransmissionParams transparams;
  /// 会话参数
  jrtplib::RTPSessionParams sessionparams;

  /// 错误代码
  int err;
};
}
}

#endif // !_RTP_RECEIVER_H_