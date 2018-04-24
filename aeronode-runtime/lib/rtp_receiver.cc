/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-14
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <functional>
#include "logger.h"
#include "rtp_receiver.h"

namespace an
{
namespace core
{
RTPReceiver::RTPReceiver(const int _portbase)
{
	portbase = _portbase;
	// time_stamp = 8000.0;
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

int RTPReceiver::start_listen()
{
	return start_listen([&] {
		this->payload_process();
	});
}

int RTPReceiver::start_listen(std::function<void(void)> _payload_process)
{
	while (1)
	{
		session.BeginDataAccess();

		if (session.GotoFirstSourceWithData())
		{
			do
			{
				while ((output_packet = session.GetNextPacket()) != NULL)
				{
					// #ifdef ENABLE_DEBUG
					// 					LOG(INFO) << "Got packet.";
					// #endif
					// 在这里处理数据
					output_buffer_size = output_packet->GetPayloadLength();
					output_buffer = (char *)output_packet->GetPayloadData();
					_payload_process();
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
#endif // !RTP_SUPPORT_THREAD
	}

	return 0;
}

// int RTPReceiver::read()
// {
// 	output_buffer_size = 1;
// 	output_buffer = (char *)calloc(1, output_buffer_size);

// 	session.BeginDataAccess();

// 	if (session.GotoFirstSourceWithData())
// 	{
// 		do
// 		{
// 			while ((output_packet = session.GetNextPacket()) != NULL)
// 			{
// 				// 在这里处理数据
// 				output_buffer_size = output_packet->GetPayloadLength();
// 				output_buffer = (char *)calloc(1, output_buffer_size);
// 				// output_buffer = (char *)calloc(output_buffer_size, 1);
// 				memcpy(output_buffer, output_packet->GetPayloadData(), output_buffer_size);

// #ifdef ENABLE_DEBUG
// 				LOG(INFO) << "Got packet.";
// #endif

// 				// 不再需要这个包了，删除之
// 				session.DeletePacket(output_packet);
// 			}
// 		} while (session.GotoNextSourceWithData());
// 	}

// 	session.EndDataAccess();

// #ifndef RTP_SUPPORT_THREAD
// 	if ((err = session.Poll()) < 0)
// 	{
// 		LOG(ERROR) << jrtplib::RTPGetErrorString(err);
// 		return -1;
// 	}
// #endif //! RTP_SUPPORT_THREAD

// 	return 0;
// }

RTPReceiver::~RTPReceiver()
{
	free(output_buffer);
	session.BYEDestroy(jrtplib::RTPTime(10, 0), 0, 0);
}
}
}
