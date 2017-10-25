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