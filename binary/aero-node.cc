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
 * Last Modified:  2018-07-03
 * Modified By:    姜阳 (j824544269@gmail.com)
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
#include "aeronode/voice_capture.h"
#include "aeronode/voice_playback.h"
#include "aeronode/an-g729/g729encoder.h"
#include "aeronode/an-g729/g729decoder.h"

using namespace std;
using namespace an::core;
using namespace an::codec;

void listen();
void send();

int main(int argc, char const *argv[])
{
    logger_init();

    ThreadPool tp(4);

    tp += [] { listen(); };
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

void listen()
{
    RTPReceiver r(8338);
    VoicePlayback vp("default");
    G729Decoder dec;
    r.start_listen([&r, &dec, &vp] {
        dec.decoder(r.output_buffer, r.output_buffer_size);
        vp.playback(dec.output_buffer, dec.output_buffer_size);
    });
}

void send()
{
    RTPSender s("127.0.0.1", 8338);
    VoiceCapture vc("default");
    G729Encoder enc;
    while (1)
    {
        vc.capture();
        enc.encoder(vc.output_buffer, vc.output_buffer_size);
        s.write(enc.output_buffer, enc.output_buffer_size);
    }
}