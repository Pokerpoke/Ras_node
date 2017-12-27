#!/bin/sh

# get the destation ip
echo "Enter destination IP (Default : 192.168.0.22) : " 
read DESTIP

if test -z ${DESTIP}
then
    DESTIP="192.168.0.22"
fi

# get CMAKE_SOURCE_DIR
CMAKE_SOURCE_DIR=$(dirname $(readlink -f "$0"))
cd ${CMAKE_SOURCE_DIR}/..

# update CMAKE_SOURCE_DIR
CMAKE_SOURCE_DIR=$(pwd)

# go to build directory
if [ ! -d ${CMAKE_SOURCE_DIR}/build ] 
then
   mkdir ${CMAKE_SOURCE_DIR}build 
fi
cd ${CMAKE_SOURCE_DIR}/build/

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
make -j

# copy files
scp -rp ./bin/* root@${DESTIP}:/home/aero-node/
scp ./lib/* root@${DESTIP}:/usr/lib/
scp -p ${CMAKE_SOURCE_DIR}/scripts/an-run root@${DESTIP}:/bin/

# ssh -l root ${DESTIP} "an-run /home/aero-node/main"