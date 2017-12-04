#!/bin/sh

# 判断wpa配置文件是否存在，不存在则创建
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
wpa_supplicant -B -Dwext -iwlan0 -c/etc/wpa_supplicant/wpa_supplicant.conf

ifconfig wlan0 down
ifconfig wlan0 up

#!/bin/sh

base=led-player

# See how we were called.
case "$1" in
  start)
                /usr/bin/$base &
        ;;
  stop)
        pid=`/bin/pidof $base`
        if [ -n "$pid" ]; then
                kill -9 $pid
        fi
        ;;
esac

exit 0