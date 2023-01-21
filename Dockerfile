FROM nvcr.io/nvidia/cuda:12.0.0-devel-ubuntu20.04

WORKDIR /subscale

RUN apt update
RUN DEBIAN_FRONTEND=nointeractive TZ=Etc/UTC apt install -y --allow-unauthenticated --no-install-recommends tzdata
RUN apt install -y --allow-unauthenticated --no-install-recommends git curl zip unzip tar pkg-config gfortran python3 cmake nano

COPY . .

RUN make init
RUN make install-dependencies
RUN make build
RUN make compile
