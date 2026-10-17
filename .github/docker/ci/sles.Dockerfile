# syntax=docker/dockerfile:1.4

ARG VMAJ
ARG VMIN
# Public base image only; see .github/workflows/ci-images.yml.
FROM registry.suse.com/bci/bci-base:${VMAJ}.${VMIN}

SHELL ["/bin/bash", "-e", "-c"]

RUN <<EOF2
zypper -n install \
  ccache \
  cmake \
  file \
  gcc \
  gcc-c++ \
  git \
  make \
  ninja \
  python3 \
  rpm-build
zypper clean -a
EOF2
