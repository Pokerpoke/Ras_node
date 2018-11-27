#!/bin/bash
################################################################################
# 
# Copyright (c) 2018 NUAA AeroLab
# 
# @author   Jiang Yang (pokerpoke@qq.com)
# @date     2018-11
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-11-22
# Modified By:    Jiang Yang (pokerpoke@qq.com)
# 
################################################################################
sudo apt-get install -y python3-venv

# get scripts directory
CMAKE_SOURCE_DIR=$(dirname $(readlink -f $0))
cd ${CMAKE_SOURCE_DIR}/../..
# update cmake source path
CMAKE_SOURCE_DIR=$(pwd)
cd ${CMAKE_SOURCE_DIR}/an-web

if [ -d venv ] 
then
   rm -rf venv 
fi

mkdir venv && cd venv
python3 -m venv .
cd ..

source venv/bin/activate

pip3 install -r requirements.txt