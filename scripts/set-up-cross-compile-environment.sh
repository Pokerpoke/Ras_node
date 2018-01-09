#!/bin/sh
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

# clone repository
# github repository
# git clone https://github.com/Pokerpoke/aero-node-tools.git
# for a high speed, will use git repository of lab LAN instead
git clone http://192.168.0.7:3000/pokerpoke/aero-node-tools.git
# mkdir aero-node-tools && cd aero-node-tools
# wget -c -t 5 https://raw.githubusercontent.com/Pokerpoke/aero-node-tools/master/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz
# wget -c -t 5 https://raw.githubusercontent.com/Pokerpoke/aero-node-tools/master/target-qte-4.8.5-to-hostpc.tgz
if [ $? -ne 0 ]
then
    echo "git clone failed, plaese try again"
    exit 1
fi

# need root permitted
cd aero-node-tools
sudo tar xvzf ./arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz -C /
sudo tar xvzf ./target-qte-4.8.5-to-hostpc.tgz -C /

# build log4cpp
# use wget to download log4cpp.tar.gz
# try for 5 times
# however it goes wrong from time to time
# wget -c -t 5 --secure-protocol=TLSv1 \
#              https://sourceforge.net/projects/log4cpp/files/log4cpp-1.1.x%20%28new%29/log4cpp-1.1/log4cpp-1.1.3.tar.gz
# if [ $? -ne 0 ]
# then
#     echo "log4cpp download failed, please try again"
#     exit 1
# fi

# unpack
tar xvzf log4cpp-1.1.3.tar.gz && cd log4cpp

# if download delete it
# if use git, will delete the project later
# rm log4cpp-1.1.3.tar.gz

# build and clean for host
# IMPORTANT: it will confilct while use suao apt install liblog4cpp
# ./configure && make && sudo make install && make clean

# build for cross compile toolschain
./configure --host=arm-linux \
            --prefix=/opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr \

make

# it is unable to pass environment variable to sudo commands
# so, use a shell script to run make install
cat > ${CMAKE_SOURCE_DIR}/scripts/temp_make-install.sh << EOF
#!/bin/sh

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

git_cmake https://github.com/j0r1/JThread.git
git_cmake https://github.com/j0r1/JRTPLIB.git
git_cmake https://github.com/BelledonneCommunications/bcg729.git

# update ldconfig
sudo ldconfig