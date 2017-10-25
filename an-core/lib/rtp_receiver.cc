#include "logger.h"
#include "rtp_receiver.h"

namespace an
{
namespace core
{
RTPReceiver::RTPReceiver(const int _portbase)
{
	portbase = _portbase;
	time_stamp = 8000.0;
	payload_type = 0;
	mark = false;
	output_buffer_size = 0;
	output_buffer = NULL;

	init();
}

int RTPReceiver::init()
{
	sessionparams.SetOwnTimestampUnit(1.0 / time_stamp);
	sessionparams.SetAcceptOwnPackets(true);

	transparams.SetPortbase(portbase);

	if ((err = session.Create(sessionparams, &transparams)) < 0)
	{
		LOG(ERROR) << "Session create failed for : " << jrtplib::RTPGetErrorString(err);
		return -1;
	}

	session.SetDefaultPayloadType(payload_type);
	session.SetDefaultMark(mark);
	session.SetDefaultTimestampIncrement(time_stamp);

	return 0;
}

int RTPReceiver::read()
{
	session.BeginDataAccess();

	if (session.GotoFirstSourceWithData())
	{
		do
		{
			while ((output_packet = session.GetNextPacket()) != NULL)
			{
				// 在这里处理数据
				output_buffer_size = output_packet->GetPayloadLength();
				output_buffer = (uint8_t *)calloc(1, output_buffer_size);
				memcpy(output_buffer, output_packet->GetPayloadData(), output_buffer_size);

#ifdef ENABLE_DEBUG
				LOG(INFO) << "Got packet";
#endif

				// 不再需要这个包了，删除之
				session.DeletePacket(output_packet);
			}
		} while (session.GotoNextSourceWithData());
	}

	session.EndDataAccess();

#ifndef RTP_SUPPORT_THREAD
	if ((err = session.Poll()) < 0)
	{
		LOG(ERROR) << jrtplib::RTPGetErrorString(err);
		return -1;
	}
#endif //! RTP_SUPPORT_THREAD

	return 0;
}

RTPReceiver::~RTPReceiver()
{
	free(output_buffer);
	session.BYEDestroy(jrtplib::RTPTime(10, 0), 0, 0);
}
}
}
