#!/usr/bin/bash

pushd ../

export LED_PROJECT=$(pwd)
export PICO_SDK_PATH=${LED_PROJECT}/code/pico-sdk
export FREERTOS_KERNEL_PATH=${LED_PROJECT}/code/FreeRTOS-Kernel

popd