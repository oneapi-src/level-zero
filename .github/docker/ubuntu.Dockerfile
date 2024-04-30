# syntax=docker/dockerfile:1.4

ARG VMAJ
ARG VMIN
FROM ghcr.io/oneapi-src/level-zero-linux-compute/ubuntu:${VMAJ}.${VMIN}

ARG VMAJ
ARG VMIN

SHELL ["/bin/bash", "-e", "-c"]

RUN <<EOF
sed -i 's/^deb/deb [arch=amd64]/' /etc/apt/sources.list
source /etc/lsb-release
echo "deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME} main restricted universe multiverse" >> /etc/apt/sources.list
echo "deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME}-updates main restricted universe multiverse" >> /etc/apt/sources.list
echo "deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME}-security main restricted universe multiverse" >> /etc/apt/sources.list
echo "deb [arch=arm64] http://ports.ubuntu.com/ubuntu-ports/ ${DISTRIB_CODENAME}-backports main restricted universe multiverse" >> /etc/apt/sources.list
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
  $(if [[ "${VMAJ}.${VMIN}" != "19.10" ]]; then echo \
  gcc-aarch64-linux-gnu \
  g++-aarch64-linux-gnu \
  $(if ((VMAJ >= 20)); then echo \
  gcc-10-aarch64-linux-gnu \
  g++-10-aarch64-linux-gnu; fi) \
  libc6:arm64 \
  libstdc++6:arm64; fi) \
  git \
  ninja-build
rm -rf /var/lib/apt/lists/*
EOF

# Make newest version of aarch64 toolchain the default and enable switching.
RUN <<EOF
shopt -s extglob
for tool in $(ls /usr/bin/aarch64-linux-gnu-*([a-z\-+])); do
    for v in $(ls /usr/bin/aarch64-linux-gnu-* | grep -o [0-9]*$ | sort | uniq); do
        if [[ -f ${tool}-${v} ]]; then
            update-alternatives --install ${tool} $(basename ${tool}) ${tool}-${v} ${v}
        fi
    done
done
EOF
