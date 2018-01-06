#!/bin/sh
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2017-12
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-01-04
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

base=main

# See how we were called.
case "$1" in
    start)
        cd /home/aero-node
        /bin an-run ./$base &
        ;;
    stop)
        pid=`/bin/pidof $base`
        if [ -n "$pid" ]; then
                kill -9 $pid
        fi
        ;;
esac

exit 0