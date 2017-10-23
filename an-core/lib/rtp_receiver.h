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

namespace an
{
namespace core
{
class RTPReceiver
{
  public:
    RTPReceiver(const int _portbase = 13374);
    ~RTPReceiver();

    int read();

    // char *output_buffer;
    uint8_t *output_buffer;
    uint32_t output_buffer_size;

  private:
    int init();

    jrtplib::RTPSession session;
    jrtplib::RTPUDPv4TransmissionParams transparams;
    jrtplib::RTPSessionParams sessionparams;

    double time_stamp;
    int err;
    int payload_type;
    int portbase;

    jrtplib::RTPPacket *output_packet;
};
}
}

#endif // !_RTP_RECEIVER_H_