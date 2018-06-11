#!/bin/bash
################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-04
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-04-26
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

sudo apt-get update
sudo apt-get install -y\
     apt-transport-https \
     ca-certificates \
     curl \
     gnupg2 \
     lsb-release \
     software-properties-common

curl -fsSL https://mirrors.ustc.edu.cn/docker-ce/linux/raspbian/gpg | sudo apt-key add -

echo "deb [arch=armhf] https://mirrors.ustc.edu.cn/docker-ce/linux/debian \
     $(lsb_release -cs) stable" | \
    sudo tee /etc/apt/sources.list.d/docker.list

sudo apt-get update
sudo apt-get install -y docker-ce
sudo usermod -a -G docker $USER
sudo bash -c 'cat > /etc/docker/daemon.json << EOF
{
  "insecure-registries":
    ["192.168.0.9:5000"]
}
EOF'
sudo systemctl restart docker
