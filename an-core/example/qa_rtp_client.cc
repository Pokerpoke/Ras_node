// #include <rtpsession.h>
// #include <rtpudpv4transmitter.h>
// #include <rtpipv4address.h>
// #include <rtpsessionparams.h>
// #include <rtperrors.h>
// #include <rtplibraryversion.h>
// #include <rtppacket.h>

// #include <iostream>

// #include "voice_capture.h"
// #include "voice_playback.h"
// #include "logger.h"

// using namespace std;
// using namespace jrtplib;
// using namespace an::core;

// int main()
// {
// 	logger_init();

// 	RTPSession session;

// 	VoiceCapture c("default");
// 	VoicePlayback p("default");

// 	LOG(INFO) << "JRTPLIB version: " << RTPLibraryVersion::GetVersion().GetVersionString();

// 	uint16_t hostport = 13372;
// 	uint32_t destip;
// 	uint32_t destport = 13374;
// 	string ip("127.0.0.1");

// 	destip = inet_addr(ip.c_str());
// 	if (destip == INADDR_NONE)
// 	{
// 		LOG(ERROR) << "Bad IP address specified";
// 		return -1;
// 	}

// 	destip = ntohl(destip);

// 	// Now, we'll create a RTP session, set the destination, send some
// 	// packets and poll for incoming data.

// 	RTPUDPv4TransmissionParams transparams;
// 	RTPSessionParams sessionparams;

// 	sessionparams.SetOwnTimestampUnit(1.0 / 10.0);
// 	sessionparams.SetAcceptOwnPackets(true);

// 	transparams.SetPortbase(hostport);

// 	int err;
// 	if ((err = session.Create(sessionparams, &transparams)) < 0)
// 	{
// 		LOG(ERROR) << RTPGetErrorString(err);
// 		return -1;
// 	}

// 	RTPIPv4Address addr(destip, destport);
// 	if ((err = session.AddDestination(addr)) < 0)
// 	{
// 		LOG(ERROR) << RTPGetErrorString(err);
// 		return -1;
// 	}

// 	session.SetDefaultPayloadType(0);
// 	session.SetDefaultMark(false);
// 	session.SetDefaultTimestampIncrement(10);

// 	for (size_t i = 0; i < 10; i++)
// 	// while(1)
// 	{
// 		// c.capture();
// 		if ((err = session.SendPacket((char *)"1234567890", 10)) < 0)
// 		// if ((err = session.SendPacket((char *)c.output_buffer, c.output_buffer_size)) < 0)
// 		{
// 			LOG(ERROR) << RTPGetErrorString(err);
// 			continue;
// 		}

// 		if ((err = session.Poll()) < 0)
// 		{
// 			LOG(ERROR) << RTPGetErrorString(err);
// 		}

// 		// RTPTime::Wait(RTPTime(1, 0));
// 	}

// 	session.BYEDestroy(RTPTime(10, 0), 0, 0);

// 	return 0;
// }



#include "rtp_sender.h"
#include "logger.h"

using namespace std;
using namespace an::core;

int main()
{
	logger_init();

	RTPSender s("127.0.0.1", 13374);
	// RTPSender s("192.168.0.22", 13374);


	char t[10];
	for (int i = 0; i < 10; i++)
	{
		t[i] = i;
		cout << t[i];
		// s.write(t, sizeof(t));
		// s.write((char *)"123", 3);
	}

	getchar();

	return 0;
}