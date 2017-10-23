#include "logger.h"
#include "rtp_receiver.h"

namespace an
{
namespace core
{
RTPReceiver::RTPReceiver(const std::string &ip,
						 const int _portbase)
{
	portbase = _portbase;
	time_stamp = 10.0;
	payload_type = 0;

	init();
}

int RTPReceiver::init()
{
	sessionparams.SetOwnTimestampUnit(1.0 / time_stamp);
	// sessionparams.SetAcceptOwnPackets(true);

	transparams.SetPortbase(portbase);

	if ((err = session.Create(sessionparams, &transparams)) < 0)
	{
		LOG(ERROR) << "Session create failed for : " << jrtplib::RTPGetErrorString(err);
		return -1;
	}

	session.SetDefaultPayloadType(payload_type);
	session.SetDefaultMark(false);
	session.SetDefaultTimestampIncrement(time_stamp);

	return 0;
}

RTPReceiver::~RTPReceiver()
{
}
}
}
