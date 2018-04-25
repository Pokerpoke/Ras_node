FROM 192.168.0.9:5000/aeronode-ci:0.1

RUN git clone http://192.168.0.9:8086/git/Pokerpoke/aero-node.git && \
    apt-get install -y sudo && \
    ./aero-node/docker/set-up-cross-compile-environment.sh && \
    rm -rf aero-node