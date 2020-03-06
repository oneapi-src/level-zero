# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT

ARG IMAGE_VERSION=eoan-20200114
FROM ubuntu:$IMAGE_VERSION

ARG http_proxy
ENV http_proxy=$http_proxy
ARG https_proxy
ENV https_proxy=$https_proxy

RUN apt-get update && apt-get install -y \
        build-essential \
        ccache \
        cmake \
        file \
        git \
        opencl-headers \
    && rm -rf /var/lib/apt/lists/*

ARG UID=0
ARG UNAME=user
ARG GID=0
RUN groupadd --non-unique --force -g $GID user_group && \
    useradd \
      --shell /bin/bash \
      -u $UID \
      -g user_group \
      --non-unique \
      --comment '' \
      --create-home \
      $UNAME
USER $UNAME
