/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-10-26
 * Modified By:    Jiang Yang (pokerpoke@qq.com)
 * 
 */
#include <thread>
#include <getopt.h>
#include <iostream>

#include "aeronode/logger.h"
#include "aeronode/an-media/voice_capture.h"
#include "aeronode/an-media/voice_playback.h"
#include "aeronode/rtp_sender.h"
#include "aeronode/rtp_receiver.h"
#include "aeronode/an-g729/g729encoder.h"
#include "aeronode/an-g729/g729decoder.h"
#include "aeronode/thread_pool.h"

using namespace std;
using namespace an::core;
using namespace an::g729;
using namespace an::media;

void help(void);

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
            help();
            return 0;
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
            help();
            break;
        }
    }
    logger_init();
    VoiceCapture c("default");
    VoicePlayback p("default");
    RTPSender s(dest_ip, dest_port);
    RTPReceiver r(listen_port);
    G729Encoder enc;
    G729Decoder dec;
    ThreadPool tp(10);

    tp.push([&] {
        while (1)
        {
            c.capture();
            enc.encoder(c.output_buffer, c.output_buffer_size);
            s.write(enc.output_buffer, enc.output_buffer_size);
        }
    });

    tp.push([&] { r.start_listen([&] {
                      dec.decoder(r.output_buffer, r.output_buffer_size);
                      p.playback(dec.output_buffer, dec.output_buffer_size);
                  }); });

    return 0;
}

void help(void)
{
    std::cout << "Usage: voice-call [OPTION]... \n"
                 "-h,--help         show help\n"
                 "-i,--dest-ip      set destnation ip address\n"
                 "-p,--dest-port    set destnation port\n"
                 "-l,--listen-port  set listen port\n";
}