#!/bin/sh

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/log4cpp \
    root@192.168.0.22:/usr/include/log4cpp

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/jrtplib3 \
    root@192.168.0.22:/usr/include/jrtplib

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/jthread \
    root@192.168.0.22:/usr/include/jthread

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/liblog4cpp.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/liblog4cpp.so* \
    root@192.168.0.22:/usr/lib/

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/libjrtp.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/libjrtp.so* \
        root@192.168.0.22:/usr/lib/

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/libjthread.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/libjthread.so* \
        root@192.168.0.22:/usr/lib/