#ifndef _RTP_RECEIVER_H_
#define _RTP_RECEIVER_H_

#include <rtpsession.h>
#include <rtpudpv4transmitter.h>
#include <rtpipv4address.h>
#include <rtpsessionparams.h>
#include <rtperrors.h>
#include <rtplibraryversion.h>
#include <rtppacket.h>

namespace an
{
namespace core
{
class RTPReceiver
{
  public:
	RTPReceiver(const std::string &ip,
				const int _portbase = 13374);
	~RTPReceiver();

  private:
	int init();

	jrtplib::RTPSession session;
	jrtplib::RTPUDPv4TransmissionParams transparams;
	jrtplib::RTPSessionParams sessionparams;

	double time_stamp;
	int err;
	int payload_type;
	int portbase;
};
}
}

#endif // !_RTP_RECEIVER_H_