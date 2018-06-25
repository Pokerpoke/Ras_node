#!/bin/bash
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-06
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-06-24
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

SCRIPT_DIR=$(dirname $(readlink -f "$0"))
cd ${SCRIPT_DIR}/../..
# update CMAKE_SOURCE_DIR
CMAKE_SOURCE_DIR=$(pwd)

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

scp -rp /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/liblog4cpp.a \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/liblog4cpp.so* \
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

scp -rp ${CMAKE_SOURCE_DIR}/scripts/Tiny4412_connect_to_wifi.sh \
        root@${DESTIP}:/home/scripts/Tiny4412_connect_to_wifi.sh

scp -rp ${CMAKE_SOURCE_DIR}/scripts/an-run \
        root@${DESTIP}:/bin/an-run