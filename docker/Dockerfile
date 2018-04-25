FROM ubuntu:16.04

COPY sources.list /etc/apt/sources.list

RUN apt-get update \
    && apt-get install -y git g++ gcc qt4-dev-tools libqtwebkit-dev libasound2-dev \
    swig3.0 liblog4cpp5-dev cmake python-dev python3-dev doxygen wget\
    && apt-get clean
RUN git clone http://192.168.0.9:8086/git/aero-node/JThread.git && \
    cd JThread && mkdir build && cd build && cmake ..  && \
    make && make install && cd .. && rm -rf JThread && \
    git clone http://192.168.0.9:8086/git/aero-node/JRTPLIB.git && \
    cd JRTPLIB && mkdir build && cd build && cmake ..  && \
    make && make install && cd .. && rm -rf JRTPLIB && \
    git clone http://192.168.0.9:8086/git/aero-node/bcg729.git && \
    cd bcg729 && mkdir build && cd build && cmake ..  && \
    make && make install && cd .. && rm -rf bcg729 && \
    mkdir aeronode-tools && cd aeronode-tools && \
    wget -c -t 5 http://192.168.0.9/share/aero-node-tools/log4cpp-1.1.3.tar.gz && \
    wget -c -t 5 http://192.168.0.9/share/aero-node-tools/target-qte-4.8.5-to-hostpc.tgz && \
    wget -c -t 5 http://192.168.0.9/share/aero-node-tools/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz && \
    tar xvzf ./arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz -C / && \
    tar xvzf ./target-qte-4.8.5-to-hostpc.tgz -C / && \
    tar xvzf log4cpp-1.1.3.tar.gz && cd log4cpp && \
    ./configure --host=arm-linux \
    --prefix=/opt/FriendlyARM/toolschain/4.5.1/arm-none-linux-gnueabi/sys-root/usr && \
    make && \
    export PATH=/opt/FriendlyARM/toolschain/4.5.1/bin:$PATH && \
    make install && \
    cd .. && rm -rf aeronode-tools

# RUN git clone http://192.168.0.9:8086/git/Pokerpoke/aero-node.git \
#     && cd aero-node && mkdir build && cd build && cmake .. && make
