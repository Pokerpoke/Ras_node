#!/bin/bash
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-05
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-05-28
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

SCRIPT_PATH=$(readlink -f "$0")

apt-get install -y git \
                   zsh \
                   htop \
                   tree \
                   vim



rm ${SCRIPT_PATH}