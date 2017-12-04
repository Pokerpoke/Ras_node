#!/bin/sh

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