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
set -e

IMAGE_NAME=2018-04-18-raspbian-stretch.img
IMAGE_PATH=~/Downloads/${IMAGE_NAME}
while getopts 'dp:m' OPT;
do
    case ${OPT} in
        d)
            wget -c -v http://192.168.0.9/share/system-images/${IMAGE_NAME} -O ~/Downloads/${IMAGE_NAME}
            IMAGE_PATH=~/Downloads/${IMAGE_NAME}
            ;;
        p)
            IMAGE_PATH=${OPTARG}
            ;;
        m)
            if [ ! -d /media/${USER}/boot ]
            then
                sudo mkdir /media/${USER}/boot
            fi
            if [ ! -d /media/${USER}/rootfs ]
            then
                sudo mkdir /media/${USER}/rootfs
            fi
            LOOP_PATH=$(sudo losetup --show -f -P ${IMAGE_PATH})
            echo "${LOOP_PATH}"
            sudo mount -w ${LOOP_PATH}p1 /media/${USER}/boot
            sudo mount -w ${LOOP_PATH}p2 /media/${USER}/rootfs
            WAIT_FOR_UNMOUNT=true
            ;;
        ?)
            echo "Usage :
            default usage is ./image-init.sh -dm
            -a use axel for high speed.
            -d download image files from 192.168.0.9.
            -p specify the image file path.
            -m mount image files.
            "
            exit 0
            ;;
    esac
done


SCRIPT_PATH=$(dirname $(readlink -f "$0"))

echo "Input dev address (default:/media/${USER}/boot and /media/${USER}/rootfs) :"
read MEDIA_PATH

if [[ -z "${MEDIA_PATH}" ]]
then
   MEDIA_PATH=/media/${USER}
fi

if [ ! -f ${MEDIA_PATH}/boot/ssh ]
then
    sudo touch ${MEDIA_PATH}/boot/ssh
fi
echo "Enable ssh."

sudo cp ${SCRIPT_PATH}/config.txt ${MEDIA_PATH}/boot/config.txt
echo "Rotate LCD screen for 180 degree."

sudo cp ${SCRIPT_PATH}/wpa_supplicant.conf ${MEDIA_PATH}/rootfs/etc/wpa_supplicant/wpa_supplicant.conf
echo "Set WiFi access."

cd ${MEDIA_PATH}/rootfs/etc/apt

if [ -f ./sources.list.d/raspi.list ]
then
    sudo mv ./sources.list.d/raspi.list ./sources.list.d/raspi.list.bak
fi

# sudo mv sources.list sources.list.bak
sudo bash -c 'cat > sources.list.rpi << EOF
deb http://mirrordirector.raspbian.org/raspbian/ stretch main contrib non-free rpi
# Uncomment line below then "apt-get update" to enable "apt-get source"
#deb-src http://archive.raspbian.org/raspbian/ stretch main contrib non-free rpi
EOF'

sudo bash -c 'cat > sources.list << EOF
deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi
#deb-src http://mirrors.ustc.edu.cn/raspbian/raspbian/ stretch main contrib non-free rpi
EOF'
echo "Change sources to USTC sources."

# sudo cp ${SCRIPT_PATH}/rpi-init.sh ${MEDIA_PATH}/rootfs/etc/init.d/rpi-init.sh
# echo "Set up rpi-init.sh for first boot."

################################################################################
# unmount and clear
################################################################################
if [ "${WAIT_FOR_UNMOUNT}" = true ] ;
then
   sudo umount ${MEDIA_PATH}/boot 
   sudo umount ${MEDIA_PATH}/rootfs
   sudo losetup -d ${LOOP_PATH}
fi