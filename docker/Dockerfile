FROM 192.168.0.9:5000/aeronode-ci:0.1

RUN git clone http://192.168.0.9:8086/git/Pokerpoke/aero-node.git && \
    cd aero-node && \
    apt-get install -y sudo && \
    ./docker/set-up-cross-compile-environment.sh && \
    mkdir build && cd build && cmake .. && make && \
    export PATH=/opt/FriendlyARM/toolschain/4.5.1/bin:$PATH && \
    mkdir Tiny4412 && cd Tiny4412 && cmake -DCMAKE_BUILD_TARGET=Tiny4412 ../../ && make