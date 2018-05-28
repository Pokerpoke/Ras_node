#!/bin/bash
################################################################################
#
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
#
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-04
# @brief    a snippet to init RPi images
# @version  0.0.1
#
# Last Modified:  2018-04-26
# Modified By:    姜阳 (j824544269@gmail.com)
#
################################################################################

echo "Input dev address (default:/media/${USER}/boot and /dev/${USER}/rootfs) :"
read MEDIA_ADDR

if [[ -z "${MEDIA_ADDR}" ]]
then
   MEDIA_ADDR=/media/${USER}
fi

if [ ! -f ${MEDIA_ADDR}/boot/ssh ]
then
    sudo touch ${MEDIA_ADDR}/boot/ssh
fi
echo "Enable ssh."

sudo cat >> ${MEDIA_ADDR}/boot/config.txt << EOF

lcd_rotate=2
EOF

echo "Rotate LCD screen for 180 degree."

cd ${MEDIA_ADDR}/rootfs/etc/wpa_supplicant
if [ ! -f wpa_supplicant.conf ]
then
    sudo touch wpa_supplicant.conf
fi

sudo bash -c 'cat >> wpa_supplicant.conf << EOF

network={
    ssid="411-D-Link"
    psk="aerolab411"
    priority=1
}

network={
    ssid="AeroNet411"
    psk="aerolab411"
    priority=2
}
EOF'
echo "Set access to 411-D-Link and AeroNet411 wifi."

cd ${MEDIA_ADDR}/rootfs/etc/apt

if [ -f ./sources.list.d/raspi.list ]
then
    sudo mv ./sources.list.d/raspi.list ./sources.list.d/raspi.list.bak
fi
sudo mv sources.list sources.list.bak
sudo bash -c 'cat > sources.list << EOF
deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi
#deb-src http://mirrors.ustc.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi
EOF'
echo "Change sources to USTC sources."

sudo cp rpi-init.sh ${MEDIA_ADDR}/rootfs/etc/init.d/rpi-init.sh
echo "Set up rpi-init.sh for first boot."
