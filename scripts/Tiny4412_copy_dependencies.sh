#!/bin/sh

scp -r /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/log4cpp \
    root@192.168.0.22:/usr/include/log4cpp

scp -r /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/jrtplib \
    root@192.168.0.22:/usr/include/jrtplib

scp -r /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/jthread \
    root@192.168.0.22:/usr/include/jthread

scp -r /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/liblog4cpp.a \
       /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/liblog4cpp.so* \
    root@192.168.0.22:/usr/lib/

scp -r /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjrtp.a \
       /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjrtp.so* \
    root@192.168.0.22:/usr/lib/

scp -r /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjthread.a \
       /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjthread.so* \
    root@192.168.0.22:/usr/lib/