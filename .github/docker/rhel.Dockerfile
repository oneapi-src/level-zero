# syntax=docker/dockerfile:1.4

ARG VMAJ
ARG VMIN

FROM ghcr.io/oneapi-src/level-zero-linux-compute/rhel:${VMAJ}.${VMIN}

SHELL ["/bin/bash", "-e", "-c"]