#include "logger.h"
#include "voice_capture.h"
#include "voice_playback.h"
#include "rtp_receiver.h"
#include "rtp_sender.h"
#include <thread>
#include <pthread.h>
#include <mutex>
#include <functional>
#include <condition_variable>

using namespace std;

an::core::VoiceCapture c("default");
an::core::VoicePlayback p("default");

class RTPReceiver : public an::core::RTPReceiver
{
  public:
	RTPReceiver(int port) : an::core::RTPReceiver(port)
	{
	}

  private:
	void payload_process();
};
void RTPReceiver::payload_process()
{
	p.playback(output_buffer, output_buffer_size);
}

class RTPSender : public an::core::RTPSender
{
  public:
	RTPSender(const std::string ip, const int port) : an::core::RTPSender(ip, port)
	{
	}
};

int main(int argc, char **argv)
{
	logger_init();
	RTPReceiver r(8338);
	RTPSender s("127.0.0.1", 8338);
	thread rt([&] { r.start_listen(); });
	thread st([&] {
		while (1)
		{
			c.capture();
			s.write(c.output_buffer, c.output_buffer_size);
		}
	});

	if (rt.joinable())
		rt.join();
	if (st.joinable())
		st.join();

	return 0;
}