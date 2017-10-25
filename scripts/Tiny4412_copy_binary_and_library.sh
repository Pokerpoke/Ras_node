#!/bin/sh

# cd ..
# if [ -d ./build ] 
# then
#     rm -rf build
# fi

# mkdir build
# cd build

cd ../build/

if [ -d ./Tiny4412 ] 
then
    rm -rf Tiny4412
fi

mkdir Tiny4412
cd Tiny4412
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_TARGET=Tiny4412 ../../
make

scp -r ./bin/* root@192.168.0.22:/home/aero-node
scp ./lib/* root@192.168.0.22:/usr/lib/