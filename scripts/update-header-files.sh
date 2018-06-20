#!/bin/bash
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-06
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-06-11
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################
set -e

# get scripts directory
CMAKE_SOURCE_DIR=$(dirname $(readlink -f $0))
cd ${CMAKE_SOURCE_DIR}/..
# update cmake source path
CMAKE_SOURCE_DIR=$(pwd)
cd ${CMAKE_SOURCE_DIR}

# copy header files
function update-header-files()
{
    if test -z "$1"
    then
        echo "please input module name"
        exit 1
    fi

    rsync $1/lib/*.h $1/include/$1/
}

rsync aeronode-runtime/lib/*.h aeronode-runtime/include/aeronode/

update-header-files an-g729
# update-header-files an-gui