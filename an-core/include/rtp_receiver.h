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
class RTPSession : public jrtplib::RTPSession
{
  public:
    char *output_buffer;
    int output_buffer_size;

  protected:
    void OnValidatedRTPPacket(jrtplib::RTPSourceData *srcdat, 
                              jrtplib::RTPPacket *rtppack, 
                              bool isonprobation, 
                              bool *ispackethandled)
    {
        output_buffer_size = rtppack->GetPayloadLength();
        output_buffer = (char *)calloc(1, output_buffer_size);
        memcpy(output_buffer, rtppack->GetPayloadData(), output_buffer_size);

		DeletePacket(rtppack);
		*ispackethandled = true;
    }
};

class RTPReceiver
{
  public:
    RTPReceiver(const int _portbase = 13374);
    ~RTPReceiver();

    int read();

    char *output_buffer;
    uint32_t output_buffer_size;

    double time_stamp;
    int payload_type;
    int portbase;
    bool mark;

  private:
    int init();

    RTPSession session;
    jrtplib::RTPUDPv4TransmissionParams transparams;
    jrtplib::RTPSessionParams sessionparams;
    jrtplib::RTPPacket *output_packet;

    int err;
};
}
}

#endif // !_RTP_RECEIVER_H_