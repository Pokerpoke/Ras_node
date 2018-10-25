/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-06
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-23
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include <chrono>
#include <unistd.h>
#include <thread>
#include "aeronode/logger.h"
#include "aeronode/udp_client.h"
#include "aeronode/udp_server.h"
#include "aeronode/tcp_client.h"
#include "aeronode/tcp_server.h"
#include "aeronode/rtp_sender.h"
#include "aeronode/rtp_receiver.h"
#include "aeronode/thread_pool.h"
#include "aeronode/an-media/voice_capture.h"
#include "aeronode/an-media/voice_playback.h"
#include "aeronode/an-g729/g729encoder.h"
#include "aeronode/an-g729/g729decoder.h"
#include "aeronode/signaling.h"

using namespace std;
using namespace an::core;
using namespace an::codec;

void listen();
void send();
void server();

int main(int argc, char const *argv[])
{
    logger_init();

    ThreadPool tp(4);

    // tp += [] { listen(); };

    tp += [] {
        server();
    };

    tp += [] { send(); };

    // configure_init
    // Thread_Pool thread_pool
    // UDP_start_listen --> (
    //     signaling_parser
    //     bind_port_and_wait_for_message
    //     return_status
    //     thread_pool += service -->(
    //         create_local_socket
    //     )

    // )

    return 0;
}

void server()
{
    // UDPServer s(13374);
    TCPServer s(13374);
    Signaling sig;
    s.start_listen([&s, &sig] {
        LOG(INFO) << sig.decoder(s.output_buffer);
    });
    // if(signaling.decoder(c.output_buffer)>0)
    // if (s.output_buffer != 0)
    // {
    // LOG(INFO) << s.output_buffer;
    // }
    // if (signaling.decoder(c.output_buffer) > 0)
    // {
    //     siganling.response();
    //     thread_pool += [] { signaling.url_parser.get_service(); };
    // }
}

// void listen()
// {
//     RTPReceiver r(8338);
//     VoicePlayback vp("default");
//     G729Decoder dec;
//     r.start_listen([&r, &dec, &vp] {
//         dec.decoder(r.output_buffer, r.output_buffer_size);
//         vp.playback(dec.output_buffer, dec.output_buffer_size);
//     });
// }
// void send()
// {
//     UDPClient c("127.0.0.1", 8338);
//     VoiceCapture vc("default");
//     G729Encoder enc;
//     while (1)
//     {
//         vc.capture();
//         enc.encoder(vc.output_buffer, vc.output_buffer_size);
//         c.write(enc.output_buffer,outputbu);
//     }
// }

void send()
{
    // UDPClient c("127.0.0.1", 13374);
    TCPClient c("127.0.0.1", 13374);
    // VoiceCapture vc("default");
    // G729Encoder enc;
    // while (1)
    for (int i = 0; i < 10; i++)
    {
        // vc.capture();
        // enc.encoder(vc.output_buffer, vc.output_buffer_size);
        c.write("12312312323");
        sleep(1);
    }
}