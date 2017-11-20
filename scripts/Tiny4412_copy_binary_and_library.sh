#!/bin/sh

read -p "Enter destation IP: " DESTIP

cd ../build/

if [ -d ./Tiny4412 ] 
then
    rm -rf Tiny4412
fi

mkdir Tiny4412
cd Tiny4412
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_BUILD_TARGET=Tiny4412 ../../
make

scp -r ./bin/* root@$DESTIP:/home/aero-node
scp ./lib/* root@$DESTIP:/usr/lib/