#include <rtpsession.h>
#include <rtpudpv4transmitter.h>
#include <rtpipv4address.h>
#include <rtpsessionparams.h>
#include <rtperrors.h>
#include <rtplibraryversion.h>
#include <rtppacket.h>

#include <iostream>

#include "voice_capture.h"
#include "voice_playback.h"
#include "logger.h"

using namespace std;
using namespace jrtplib;
using namespace an::core;

int main()
{
    RTPSession session;

    uint16_t hostport = 13374;

    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessionparams;

    sessionparams.SetOwnTimestampUnit(1.0 / 10.0);
    sessionparams.SetAcceptOwnPackets(true);

    transparams.SetPortbase(hostport);

    int err;
    // status = session.Create(sessionparams, &transparams);
    if ((err = session.Create(sessionparams, &transparams)) < 0)
    {
        LOG(ERROR) << RTPGetErrorString(err);
        return -1;
    }

    session.SetDefaultPayloadType(0);
    session.SetDefaultMark(false);
    session.SetDefaultTimestampIncrement(10);

    while (1)
    {

        session.BeginDataAccess();

        if (session.GotoFirstSourceWithData())
        {
            do
            {
                RTPPacket *pack;

                while ((pack = session.GetNextPacket()) != NULL)
                {
                    // You can examine the data here
                    cout << pack->GetPayloadData();
                    // p.playback((char *)pack->GetPayloadData(), pack->GetPayloadLength());
                    printf("Got packet !\n");

                    // we don't longer need the packet, so
                    // we'll delete it
                    session.DeletePacket(pack);
                }
            } while (session.GotoNextSourceWithData());
        }

        session.EndDataAccess();

        if ((err = session.Poll()) < 0)
        {
            LOG(ERROR) << RTPGetErrorString(err);
        }
    }

    session.BYEDestroy(RTPTime(10, 0), 0, 0);

    return 0;
}