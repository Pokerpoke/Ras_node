#!/bin/sh

# get scripts directory
CMAKE_SOURCE_DIR=$(dirname $(readlink -f $0))
cd ${CMAKE_SOURCE_DIR}/..
# update work path
CMAKE_SOURCE_DIR=$(pwd)
SYS_ROOT_DIR="/opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root"
# echo ${CMAKE_SOURCE_DIR}
cd scripts

# cross compile necessary libraries
DEPENDENCIES=(
    git
    lib32z1
    cmake
)

for DEP in DEPENDENCIES ; do
    dpkg --get-selections | grep ${DEP}
    if [ $? -ne 0 ]
    then
        echo "${DEP} is required, but not installed, going to install it."
        sudo apt install -y ${DEP}
        if [ $? -ne 0 ]
        then
            exit 1
        fi
    fi
done

# if exist, clean it
if [ -d aero-node-tools ]
then
    rm -rf aero-node-tools
fi

# clone repository
# github repository
# git clone https://github.com/Pokerpoke/aero-node-tools.git
# for a high speed, will use git repository of lab instead
# TODO: use git
# git clone http://192.168.0.7:3000/pokerpoke/aero-node-tools.git
mkdir aero-node-tools && cd aero-node-tools
wget -c -t 5 https://raw.githubusercontent.com/Pokerpoke/aero-node-tools/master/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz
wget -c -t 5 https://raw.githubusercontent.com/Pokerpoke/aero-node-tools/master/target-qte-4.8.5-to-hostpc.tgz
if [ $? -ne 0 ]
then
    echo "wget failed, plaese try again"
    exit 1
fi

# need root permitted
# cd aero-node-tools
sudo tar xvzf ./arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz -C /
sudo tar xvzf ./target-qte-4.8.5-to-hostpc.tgz -C /

# clean
cd ..
rm -rf aero-node-tools

# add to path
export PATH=/opt/FriendlyARM/toolschain/4.5.1/bin:$PATH

# build JThread
# if exist, clean it
if [ -d JThread ]
then
    rm -rf JThread
fi

# preparation
JTHREAD_DIR="${CMAKE_SOURCE_DIR}/scripts/JThread"
git clone https://github.com/j0r1/JThread.git
if [ $? -ne 0 ]
then
    echo "git clone failed, plaese try again"
    exit 1
fi
cd JThread
# build for host
mkdir build && cd build && cmake .. && make && sudo make install && cd .. && rm -rf build
# build for cross compile toolschain
# copy toolschain file
mkdir cmake/toolschain && cp -vR ${CMAKE_SOURCE_DIR}/cmake/toolschain/Tiny4412.cmake ./cmake/toolschain/

# insert cmake toolschain file path into CMakeLists.txt
sed -i "1i \
set(CMAKE_TOOLCHAIN_FILE ${JTHREAD_DIR}/cmake/toolschain/Tiny4412.cmake)" CMakeLists.txt

# build
mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=${SYS_ROOT_DIR}/usr/ ..
if [ $? -ne 0 ]
then
    echo "cmake build failed, please check output for more infomation."
    exit 1
fi
make && sudo make install

# clean and go back to cmake source directory
cd ${CMAKE_SOURCE_DIR}/scripts && rm -rf JThread

# build JRTPLIB
# if exist, clean it
if [ -d JRTPLIB ]
then
    rm -rf JRTPLIB
fi

# preparation
JRTPLIB_DIR="${CMAKE_SOURCE_DIR}/scripts/JRTPLIB"
git clone https://github.com/j0r1/JRTPLIB.git
if [ $? -ne 0 ]
then
    echo "git clone failed, plaese try again"
    exit 1
fi
cd JRTPLIB
# build for host
mkdir build && cd build && cmake .. && make && sudo make install && cd .. && rm -rf build
# build for cross compile toolschain
# copy toolschain file
mkdir cmake/toolschain && cp -vR ${CMAKE_SOURCE_DIR}/cmake/toolschain/Tiny4412.cmake ./cmake/toolschain/

# insert cmake toolschain file path into CMakeLists.txt
sed -i "1i \
set(CMAKE_TOOLCHAIN_FILE ${JRTPLIB_DIR}/cmake/toolschain/Tiny4412.cmake)" CMakeLists.txt

# build
mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=${SYS_ROOT_DIR}/usr/ ..
if [ $? -ne 0 ]
then
    echo "cmake build failed, please check output for more infomation."
    exit 1
fi
make && sudo make install

# clean and go back to cmake source directory
cd ${CMAKE_SOURCE_DIR}/scripts && rm -rf JRTPLIB

# build log4cpp
# use wget to download log4cpp.tar.gz
# try for 5 times
wget -c -t 5 --user-agent="Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0" \
             --secure-protocol=TLSv1 \
             https://sourceforge.net/projects/log4cpp/files/log4cpp-1.1.x%20%28new%29/log4cpp-1.1/log4cpp-1.1.3.tar.gz
            #  --no-check-certificate \
if [ $? -ne 0 ]
then
    echo "log4cpp download failed, please try again"
    exit 1
fi
tar xvzf log4cpp-1.1.3.tar.gz
# delete it
rm log4cpp-1.1.3.tar.gz

cd log4cpp

# build for host
./configure && make && sudo make install && make clean

# build for cross compile toolschain
./configure --host=arm-linux \
            --prefix=/opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr \

make

# it is unable to pass environment variable to sudo commands
# so, I use a shell script to run make install
sudo bash ../make-install.sh

# clean
cd ${CMAKE_SOURCE_DIR}/scripts && rm -rf log4cpp
