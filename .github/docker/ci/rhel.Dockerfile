# syntax=docker/dockerfile:1.4

ARG VMAJ
ARG VMIN
# Public base image only; see .github/workflows/ci-images.yml.
FROM registry.access.redhat.com/ubi${VMAJ}/ubi:${VMAJ}.${VMIN}

ARG VMAJ

SHELL ["/bin/bash", "-e", "-c"]

# UBI repos lack ninja-build and ccache; EPEL provides both.
RUN <<EOF2
dnf -y install https://dl.fedoraproject.org/pub/epel/epel-release-latest-${VMAJ}.noarch.rpm
dnf -y install \
  ccache \
  cmake \
  file \
  gcc \
  gcc-c++ \
  git \
  make \
  ninja-build \
  python3 \
  rpm-build
dnf clean all
EOF2
