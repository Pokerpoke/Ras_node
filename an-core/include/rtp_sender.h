/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-02
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
class RTPSender
{
public:
    RTPSender(const std::string ip,
              const int port = 13374);
    ~RTPSender();

    int write(const char *input_bufffer,
              const int input_buffer_size);

    std::string dest_ip;
    int dest_port;
    int host_port;
    int payload_type;
    double time_stamp;
    bool mark;

private:
    int init();

    jrtplib::RTPSession session;
    jrtplib::RTPUDPv4TransmissionParams transparams;
    jrtplib::RTPSessionParams sessionparams;

    int err;
};
}
}

#endif // !_RTP_SENDER_H_