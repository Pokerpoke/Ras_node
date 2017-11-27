#!/bin/sh

echo "Enter destation IP : "
echo "Default : 192.168.0.22"
read DESTIP

if test -z $DESTIP
then
    DESTIP="192.168.0.22"
fi

cd ../

ROOT_DIR=$(dirname $(readlink -f "$0"))

cd $ROOT_DIR/build/

# if directory exists delete it
if [ -d ./Tiny4412 ] 
then
    rm -rf Tiny4412
fi

mkdir Tiny4412
cd Tiny4412

# make
# cmake -DCMAKE_BUILD_TYPE=Debug \
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_BUILD_TARGET=Tiny4412 ../../
make

# copy files
scp -rp ./bin/* root@$DESTIP:/home/aero-node/
scp ./lib/* root@$DESTIP:/usr/lib/
scp -p $ROOT_DIR/scripts/an-run root@$DESTIP:/bin/