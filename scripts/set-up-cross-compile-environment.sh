#!/bin/sh

# get work path
cd ..
CMAKE_SOURCE_DIR=$(dirname $(readlink -f $0))
SYS_ROOT_DIR="/opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root"
echo $CMAKE_SOURCE_DIR
cd scripts

# croess compile need i386 libraries
dpkg --get-selections | grep libc6:i386
if [ $? -ne 0 ]
then
	echo "libc6:i386 is required, but not installed, and going to install it."
	sudo apt install libc6:i386
	if [ $? -ne 0 ]
	then
		exit 1
	fi
fi

# get git repository address
echo "Input arm-linux-gcc git repositories:"
echo "(default http://192.168.0.7:3000/pokerpoke/arm-linux-toolschain.git)"
read GIT_REPO

if [ -d arm-linux-toolschain ]
then
	rm -rf arm-linux-toolschain
fi

# if empty, set to default
if test -z $GIT_REPO
then
    GIT_REPO="http://192.168.0.7:3000/pokerpoke/arm-linux-toolschain.git"
fi

# clone repository
git clone $GIT_REPO
if [ $? -ne 0 ]
then
	echo "git clone failed"
	exit 1
fi

# need root permitted
sudo tar xvzf ./arm-linux-toolschain/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz -C /

# clean
rm -rf arm-linux-toolschain

# add to path
export PATH=/opt/FriendlyARM/toolschain/4.5.1/bin:$PATH
arm-linux-gcc --version

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
	echo "git clone failed."
	exit 1
fi
cd JThread
mkdir cmake/toolschain
# copy toolschain file
cp -vR ${CMAKE_SOURCE_DIR}/cmake/toolschain/Tiny4412.cmake ./cmake/toolschain/

# insert cmake toolschain file path into CMakeLists.txt
sed -i "1i \
set(CMAKE_TOOLCHAIN_FILE ${JTHREAD_DIR}/cmake/toolschain/Tiny4412.cmake)" CMakeLists.txt

# build
mkdir build
cd build
cmake DCMAKE_INSTALL_PREFIX=${SYS_ROOT_DIR}/usr/ ..
if [ $? -ne 0 ]
then
	echo "cmake build failed, please check output for more infomation."
	exit 1
fi
make
sudo make install

# clean and go back to cmake source directory
rm -rf JThread
cd ${CMAKE_SOURCE_DIR}/scripts
