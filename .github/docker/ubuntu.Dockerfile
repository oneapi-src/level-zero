# syntax=docker/dockerfile:1.4

ARG VMAJ
ARG VMIN
FROM ghcr.io/oneapi-src/level-zero-linux-compute/ubuntu:${VMAJ}.${VMIN}

ARG VMAJ
ARG VMIN

SHELL ["/bin/bash", "-e", "-c"]

RUN <<EOF
source /etc/lsb-release
if ((VMAJ < 24)); then
    sed -i 's/^deb/deb [arch=amd64]/' /etc/apt/sources.list
    cat >> /etc/apt/sources.list <<EOF2
deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME} main restricted universe multiverse
deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME}-updates main restricted universe multiverse
deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME}-security main restricted universe multiverse
deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME}-backports main restricted universe multiverse
EOF2
else
    sed -i '/^Components:/a Architectures: amd64' /etc/apt/sources.list.d/ubuntu.sources
    cat >> /etc/apt/sources.list.d/ubuntu.sources <<EOF2

types: deb
URIs: http://ports.ubuntu.com/ubuntu-ports/
Suites: ${DISTRIB_CODENAME} ${DISTRIB_CODENAME}-updates ${DISTRIB_CODENAME}-security ${DISTRIB_CODENAME}-backports
Components: main universe restricted multiverse
Architectures: arm64
Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg
EOF2
fi
dpkg --add-architecture arm64
EOF

ENV DEBIAN_FRONTEND=noninteractive
# /etc/apt/apt.conf.d/docker-clean doesn't work on older versions of docker for U2204 containers
RUN --mount=type=cache,target=/var/cache/apt <<EOF
rm /etc/apt/apt.conf.d/docker-clean
apt-get update
apt-get install -y \
  build-essential \
  ccache \
  cmake \
  universal-ctags \
  curl \
  elfutils \
  file \
  gcc-aarch64-linux-gnu \
  g++-aarch64-linux-gnu \
  libc6:arm64 \
  libstdc++6:arm64 \
  git \
  ninja-build
rm -rf /var/lib/apt/lists/*
EOF