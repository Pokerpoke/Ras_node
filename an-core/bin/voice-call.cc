#include "logger.h"
#include "voice_capture.h"
#include "voice_playback.h"
#include "rtp_receiver.h"
#include "rtp_sender.h"
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>

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
	struct option long_option[] =
		{
			{"help", 0, NULL, 'h'},
			{"dest-ip", 1, NULL, 'i'},
			{"dest-port", 1, NULL, 'p'},
			{"listen-port", 1, NULL, 'l'},
		};
	string dest_ip = "127.0.0.1";
	int dest_port = 8338;
	int listen_port = 8338;
	while (1)
	{
		int c;
		if ((c = getopt_long(argc, argv, "hi:p:l:", long_option, NULL)) < 0)
			break;
		switch (c)
		{
		case 'h':
			break;
		case 'i':
			dest_ip = strdup(optarg);
			break;
		case 'p':
			dest_port = atoi(optarg);
			break;
		case 'l':
			listen_port = atoi(optarg);
			break;
		default:
			break;
		}
	}
	logger_init();
	RTPReceiver r(listen_port);
	RTPSender s(dest_ip, dest_port);
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