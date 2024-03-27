# syntax=docker/dockerfile:1.4

ARG VMAJ
ARG VMIN

FROM ghcr.io/oneapi-src/level-zero-linux-compute/sles-15.2:latest AS sles-15.2
FROM ghcr.io/oneapi-src/level-zero-linux-compute/sles-15.3:latest AS sles-15.3
FROM ghcr.io/oneapi-src/level-zero-linux-compute/sles-15.4:latest AS sles-15.4
FROM sles-${VMAJ}.${VMIN}

SHELL ["/bin/bash", "-e", "-c"]