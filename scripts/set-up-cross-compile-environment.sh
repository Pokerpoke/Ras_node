#!/bin/bash
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-01
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-01-08
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

# get scripts directory
CMAKE_SOURCE_DIR=$(dirname $(readlink -f $0))
cd ${CMAKE_SOURCE_DIR}/..
# update work path
CMAKE_SOURCE_DIR=$(pwd)
SYS_ROOT_DIR="/opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root"
cd scripts

# cross compile necessary libraries
DEPENDENCIES=(
              "git"
              "lib32z1"
              "cmake"
              "build-essential"
              "liblog4cpp5-dev"
              "qt4-dev-tools"
              "libqtwebkit-dev"
              "libasound2-dev"
              )

for DEP in ${DEPENDENCIES[@]} ; do
    dpkg --get-selections | grep "${DEP}"
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

mkdir ${CMAKE_SOURCE_DIR}/scripts/aero-node-tools && cd ${CMAKE_SOURCE_DIR}/scripts/aero-node-tools

wget -c -t 5 http://192.168.0.9/share/aero-node-tools/log4cpp-1.1.3.tar.gz
wget -c -t 5 http://192.168.0.9/share/aero-node-tools/target-qte-4.8.5-to-hostpc.tgz
wget -c -t 5 http://192.168.0.9/share/aero-node-tools/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz

# need root permitted
sudo tar xvzf ./arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz -C /
sudo tar xvzf ./target-qte-4.8.5-to-hostpc.tgz -C /

# unpack
tar xvzf log4cpp-1.1.3.tar.gz && cd log4cpp

# build and clean for host
# IMPORTANT: it will confilct while use suao apt install liblog4cpp
# 
# ./configure && make && sudo make install && make clean

# build for cross compile toolschain
./configure --host=arm-linux \
            --prefix=/opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr \

make

# it is unable to pass environment variable to sudo commands
# so, use a shell script to run make install
cat > ${CMAKE_SOURCE_DIR}/scripts/temp_make-install.sh << EOF
#!/bin/bash

export PATH=/opt/FriendlyARM/toolschain/4.5.1/bin:$PATH

make install
EOF
sudo bash ${CMAKE_SOURCE_DIR}/scripts/temp_make-install.sh
rm ${CMAKE_SOURCE_DIR}/scripts/temp_make-install.sh

# clean
cd ${CMAKE_SOURCE_DIR}/scripts 
rm -rf aero-node-tools

# add to path
export PATH=/opt/FriendlyARM/toolschain/4.5.1/bin:$PATH

function git_cmake()
{
    if test -z "$1"
    then
        echo "please input git repository"
        exit 1
    fi

    # if exist, clean it
    cd ${CMAKE_SOURCE_DIR}/scripts 
    if [ -d temp ]
    then
        rm -rf temp
    fi

    # preparation
    PROJECT_DIR="${CMAKE_SOURCE_DIR}/scripts/temp"
    git clone $1 temp
    if [ $? -ne 0 ]
    then
        echo "git clone failed, plaese try again"
        exit 1
    fi
    cd ${PROJECT_DIR}
    # build for host
    mkdir build && cd build && cmake .. && make && sudo make install && cd .. && rm -rf build

    # build for cross compile toolschain
    # copy toolschain file
    mkdir -p cmake/toolschain && cp -vR ${CMAKE_SOURCE_DIR}/cmake/toolschain/Tiny4412.cmake ./cmake/toolschain/

    # insert cmake toolschain file path into CMakeLists.txt
    sed -i "1i \
    set(CMAKE_TOOLCHAIN_FILE ${PROJECT_DIR}/cmake/toolschain/Tiny4412.cmake)" CMakeLists.txt

    # build
    mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=${SYS_ROOT_DIR}/usr/ ..
    if [ $? -ne 0 ]
    then
        echo "cmake build failed, please check output for more infomation."
        exit 1
    fi
    make && sudo make install

    # clean
    cd ${CMAKE_SOURCE_DIR}/scripts && rm -rf ${PROJECT_DIR}
}

git_cmake http://192.168.0.9:8086/git/Pokerpoke/JThread.git
git_cmake http://192.168.0.9:8086/git/Pokerpoke/JRTPLIB.git
git_cmake http://192.168.0.9:8086/git/Pokerpoke/bcg729.git

# update ldconfig
sudo ldconfig