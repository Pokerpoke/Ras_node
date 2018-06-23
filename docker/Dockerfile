FROM ubuntu:16.04

COPY sources.list /etc/apt/sources.list

RUN apt-get update \
    && apt-get install -y \
    git \
    g++ \
    gcc \
    cmake \
    python-dev \
    python3-dev \
    doxygen \
    wget \
    lib32z1 \
    swig3.0 \
    libqt4-dev \
    libqtwebkit-dev \
    libasound2-dev \
    liblog4cpp5-dev \
    graphviz \
    sudo \
    wget \
    && apt-get clean \
    && bash -c "$(wget http://192.168.0.9/git/Pokerpoke/aero-node/raw/master/scripts/set-up-cross-compile-environment.sh -O -)"