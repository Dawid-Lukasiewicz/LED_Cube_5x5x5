#!/usr/bin/bash

source ./setenv.sh

BUILD_DIR=./build
# BUILD_TYPE="MinSizeRel"
BUILD_TYPE="Release"
# BUILD_TYPE="Debug"

ENABLE_MULTICORE=1

cmake -B ${BUILD_DIR} -DPICO_BOARD="pico_w" -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DMULTICORE_BUILD=${ENABLE_MULTICORE}
pushd ${BUILD_DIR}
make clean
make -j6
popd