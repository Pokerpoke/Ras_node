#!/bin/sh

# get the destation ip
echo "Enter destination IP (Default : 192.168.0.22) : " 
read DESTIP

if test -z ${DESTIP}
then
    DESTIP="192.168.0.22"
fi

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/log4cpp \
        root@${DESTIP}:/usr/include/log4cpp

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/jrtplib3 \
        root@${DESTIP}:/usr/include/jrtplib

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/jthread \
        root@${DESTIP}:/usr/include/jthread

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/include/bcg729 \
        root@${DESTIP}:/usr/include/bcg729

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/liblog4cpp.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/lib/liblog4cpp.so* \
        root@${DESTIP}:/usr/lib/

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjrtp.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjrtp.so* \
        root@${DESTIP}:/usr/lib/

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjthread.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjthread.so* \
        root@${DESTIP}:/usr/lib/

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libbcg729.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libbcg729.so* \
        root@${DESTIP}:/usr/lib/