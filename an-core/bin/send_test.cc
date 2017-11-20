#include <rtpsession.h>
#include <rtpudpv4transmitter.h>
#include <rtpipv4address.h>
#include <rtpsessionparams.h>
#include <rtperrors.h>
#include <rtplibraryversion.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "logger.h"
#include "voice_capture.h"

using namespace jrtplib;
using namespace an::core;

void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
		exit(-1);
	}
}

int main(void)
{
#ifdef ENABLE_DEBUG
	logger_init();
#else
	logger_init("send_test.log", AN_LOG_WARN);
#endif

	RTPSession sess;
	VoiceCapture c("default");
	uint16_t portbase = 13372;
	uint16_t destport = 13374;
	uint32_t destip;
	std::string ipstr = "127.0.0.1";
	int status, i;
	// int num = 10;
	int payload_type = 0;
	int time_stamp = 10;
	bool mark = false;

	destip = inet_addr(ipstr.c_str());
	if (destip == INADDR_NONE)
	{
		std::cerr << "Bad IP address specified" << std::endl;
		return -1;
	}

	// The inet_addr function returns a value in network byte order, but
	// we need the IP address in host byte order, so we use a call to
	// ntohl
	destip = ntohl(destip);

	// Now, we'll create a RTP session, set the destination, send some
	// packets and poll for incoming data.
	RTPUDPv4TransmissionParams transparams;
	RTPSessionParams sessparams;

	// IMPORTANT: The local timestamp unit MUST be set, otherwise
	//            RTCP Sender Report info will be calculated wrong
	// In this case, we'll be sending 10 samples each second, so we'll
	// put the timestamp unit to (1.0/10.0)
	sessparams.SetOwnTimestampUnit(1.0 / 8000.0);

	sessparams.SetAcceptOwnPackets(true);
	transparams.SetPortbase(portbase);
	status = sess.Create(sessparams, &transparams);
	checkerror(status);

	RTPIPv4Address addr(destip, destport);

	status = sess.AddDestination(addr);
	checkerror(status);

	sess.SetDefaultPayloadType(payload_type);
	sess.SetDefaultMark(mark);
	sess.SetDefaultTimestampIncrement(time_stamp);

	// for (i = 1; i <= num; i++)
	while (1)
	{
		// send the packet
		c.capture();
		status = sess.SendPacket((void *)c.output_buffer, c.output_buffer_size);
		checkerror(status);
	}

	sess.BYEDestroy(RTPTime(10, 0), 0, 0);

	return 0;
}
