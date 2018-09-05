#!/bin/sh
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-01
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-01-08
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################
INTERFACE=wlan0

while getopts 'i:' OPT;
do
    case ${OPT} in
        i)
            INTERFACE=${OPTARG}
            ;;
        ?)
            echo "Useage :
            -i specify interface(default: wlan0)
            "
            exit 0
            ;;
    esac
done

# create configure file when there is no configure file
if [ ! -d /etc/wpa_supplicant ] 
then
    mkdir /etc/wpa_supplicant
fi

if [ ! -f /etc/wpa_supplicant/wpa_supplicant.conf ] 
then
cat > /etc/wpa_supplicant/wpa_supplicant.conf << EOF
ctrl_interface=/var/run/wpa_supplicant
ap_scan=1

network={
    ssid="411-D-Link"
    psk="aerolab411"
    priority=2
}

network={
    ssid="AeroNet411"
    psk="aerolab411"
    priority=3
}

network={
    ssid="409"
    psk="aerolab409"
    priority=1
}
EOF
fi

# -B run in background
# -D drvier, wext means generic driver
# -i interface, network interface
# -c configure files
if [ -f /var/run/wpa_supplicant/wlan0 ]
then
    rm /var/run/wpa_supplicant/wlan0
fi
wpa_supplicant -B -Dwext -i${INTERFACE} -c/etc/wpa_supplicant/wpa_supplicant.conf

# restart ${INTERFACE} to work
ifconfig ${INTERFACE} down
ifconfig ${INTERFACE} up

# remove dsr
lsmod | grep dsr
if [ $? -eq 0 ]
then
    rmmod dsr
fi

# dhcp
udhcpc -i ${INTERFACE}