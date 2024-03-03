#!/usr/bin/bash

source ./setenv.sh

BUILD_DIR=./build

cmake -B ${BUILD_DIR} -DPICO_BOARD="pico_w"
pushd ${BUILD_DIR}
make -j6
popd