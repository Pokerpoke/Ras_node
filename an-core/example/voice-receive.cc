/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-09
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <rtpsession.h>
#include <rtpudpv4transmitter.h>
#include <rtpipv4address.h>
#include <rtpsessionparams.h>
#include <rtperrors.h>
#include <rtppacket.h>
#include <rtplibraryversion.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "config.h"

#include "aero-node/logger.h"
#include "aero-node/voice_playback.h"

using namespace jrtplib;
using namespace an::core;

void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        LOG(ERROR) << "ERROR: " << RTPGetErrorString(rtperr);
        exit(-1);
    }
}

int main(void)
{
#ifdef AN_TARGET_TINY4412
    logger_init("voice-receive.log", AN_LOG_INFO);
#else
    logger_init();
#endif

    RTPSession sess;
    VoicePlayback p("default");
    uint16_t portbase = 8338;
    int status;
    int time_stamp = 8000;

    // Now, we'll create a RTP session, set the destination, send some
    // packets and poll for incoming data.
    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;

    // IMPORTANT: The local timestamp unit MUST be set, otherwise
    //            RTCP Sender Report info will be calculated wrong
    // In this case, we'll be sending 10 samples each second, so we'll
    // put the timestamp unit to (1.0/10.0)
    sessparams.SetOwnTimestampUnit(1.0 / time_stamp);

    sessparams.SetAcceptOwnPackets(true);
    transparams.SetPortbase(portbase);
    status = sess.Create(sessparams, &transparams);
    checkerror(status);

    while (1)
    {
        checkerror(status);

        sess.BeginDataAccess();

        // check incoming packets
        if (sess.GotoFirstSourceWithData())
        {
            do
            {
                RTPPacket *pack;

                while ((pack = sess.GetNextPacket()) != NULL)
                {
                    // You can examine the data here
                    p.playback((char *)pack->GetPayloadData(),
                               pack->GetPayloadLength());

                    // we don't longer need the packet, so
                    // we'll delete it
                    sess.DeletePacket(pack);
                }
            } while (sess.GotoNextSourceWithData());
        }

        sess.EndDataAccess();

#ifndef RTP_SUPPORT_THREAD
        status = sess.Poll();
        checkerror(status);
#endif // RTP_SUPPORT_THREAD
    }

    sess.BYEDestroy(RTPTime(10, 0), 0, 0);
    return 0;
}
