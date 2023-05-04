FROM ubuntu:latest
USER root
RUN apt update
RUN apt install -y apt-utils
RUN apt install -y g++
RUN apt install -y cmake
RUN apt install -y libboost-all-dev
RUN apt install -y wget
RUN apt  install -y libpq-dev


WORKDIR /
RUN wget -c https://github.com/emweb/wt/archive/4.9.1.tar.gz && tar xvxf 4.9.1.tar.gz
WORKDIR /wt-4.9.1/
WORKDIR build
RUN cmake ..
RUN make
RUN make install
RUN ldconfig

WORKDIR /calendula/

