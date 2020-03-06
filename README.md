# Contents
This repo contains the following:
- oneAPI Level Zero Specification API C/C++ header files.
  https://spec.oneapi.com/versions/latest/elements/l0/source/index.html

- oneAPI Level Zero loader

# Building
Project is defined using [CMake](https://cmake.org/).

**Linux**:
Executable and binaries will be in **build/bin**
~~~~
mkdir build
cd build
cmake {path_to_source_dir}
make [package]
~~~~

**Linux with Docker**:
~~~bash
mkdir build
mkdir -p .ccache

docker run \
  --rm \
  -v $PWD:$PWD \
  -w $PWD/build \
  -e CCACHE_DIR=$PWD/.ccache \
  -e CCACHE_BASEDIR=$PWD \
  $(docker build -q \
      --build-arg UID=$(id -u) \
      --build-arg GID=$(id -g) \
      - < docker/build-linux.Dockerfile) \
  cmake \
    -G Ninja \
    -D CMAKE_C_COMPILER_LAUNCHER=ccache \
    -D CMAKE_CXX_COMPILER_LAUNCHER=ccache \
    -D CMAKE_BUILD_TYPE=Release \
    ..

docker run \
  --rm \
  -v $PWD:$PWD \
  -w $PWD/build \
  -e CCACHE_DIR=$PWD/.ccache \
  -e CCACHE_BASEDIR=$PWD \
  $(docker build -q \
      --build-arg UID=$(id -u) \
      --build-arg GID=$(id -g) \
      - < docker/build-linux.Dockerfile) \
  cmake --build . --config Release
~~~
