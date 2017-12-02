/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author 姜阳 (j824544269@gmail.com)
 * @date 2017-11-27
 * @brief 
 * @version 0.0.1
 * -----
 * Last Modified: 2017-12-02
 * Modified By: 姜阳 (j824544269@gmail.com>)
 * 
 */
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
using namespace std;

void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
		exit(-1);
	}
}

int main(int argc, char *argv[])
{
#ifdef AN_TARGET_TINY4412
	logger_init("voice-send.log", AN_LOG_INFO);
#else
	logger_init();
#endif

	RTPSession sess;
	VoiceCapture c("default");
	uint16_t destport = 8338;
	uint32_t destip;
	std::string ipstr;
	int status;
	int payload_type = 0;
	int time_stamp = 8000;
	bool mark = false;

	if (argc == 1)
	{
		ipstr = "127.0.0.1";
	}
	else
	{
		ipstr = argv[1];
	}

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
	// transparams.SetPortbase(portbase);
	status = sess.Create(sessparams, &transparams);
	checkerror(status);

	RTPIPv4Address addr(destip, destport);

	status = sess.AddDestination(addr);
	checkerror(status);

	sess.SetDefaultPayloadType(payload_type);
	sess.SetDefaultMark(mark);
	sess.SetDefaultTimestampIncrement(time_stamp);

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
