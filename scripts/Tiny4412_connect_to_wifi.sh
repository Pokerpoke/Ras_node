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

# 判断wpa配置文件是否存在，不存在则创建
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
}
EOF
fi

# -B 后台运行
# -D 驱动，wext通用驱动
# -i interface 网卡接口
# -c 配置文件
wpa_supplicant -B -Dwext -i${INTERFACE} -c/etc/wpa_supplicant/wpa_supplicant.conf

# restart ${INTERFACE} to work
ifconfig ${INTERFACE} down
ifconfig ${INTERFACE} up

# remove dsr
lsmod | grep dsr
if [ $? -e 0 ]
then
    rmmod dsr
fi

# dhcp
udhcpc -i ${INTERFACE}