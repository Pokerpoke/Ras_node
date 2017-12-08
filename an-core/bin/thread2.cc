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

// using namespace an::core;
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

int main(int argc, char **argv)
{

	logger_init();
	RTPReceiver r(8338);
	an::core::RTPSender s("192.168.2.4", 8388);
	thread rt([&] { r.start_listen(); });
	thread st([&] {
		while (1)
		{
			c.capture();
			s.write(c.output_buffer, c.output_buffer_size);
		}
	});

	for (int i = 0; i < 100; i++)
	{
		LOG(ERROR) << i;
		sleep(1);
	}

	// rt.jion();
	// st.jion();

	getchar();

	return 0;
}