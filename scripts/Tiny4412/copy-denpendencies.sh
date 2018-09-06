#!/bin/bash
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-06
# @brief    Copy aero-node dependencies to Tiny4412.
# @version  0.0.1
# 
# Last Modified:  2018-09-06
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

cd ${CMAKE_SOURCE_DIR}/scripts && mkdir -p temp/usr/lib && mkdir -p temp/usr/bin

cd temp

cp -p   /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/liblog4cpp.a      \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/liblog4cpp.so*    \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjrtp.a         \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjrtp.so*       \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjthread.a      \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libjthread.so*    \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libbcg729.a       \
        /opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr/lib/libbcg729.so*     \
        ./usr/lib/

cp ${CMAKE_SOURCE_DIR}/scripts/Tiny4412/connect-to-wifi ${CMAKE_SOURCE_DIR}/scripts/an-run          \
    ./usr/bin/

tar -cvpf aero-node-dependencies.tar usr/
scp -rp aero-node-dependencies.tar root@${DESTIP}:/home/

cd ${CMAKE_SOURCE_DIR}/scripts && rm -rf temp

ssh root@${DESTIP} "tar -xvpf /home/aero-node-dependencies.tar -C /"