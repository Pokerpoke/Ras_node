FROM 192.168.0.9:5000/aeronode-ci:0.1

RUN git clone http://192.168.0.9:8086/git/Pokerpoke/aero-node.git && \
    cd aero-node && \
    apt-get install -y sudo && \
    ./docker/set-up-cross-compile-environment.sh