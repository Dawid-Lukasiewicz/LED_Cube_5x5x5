#!/usr/bin/bash

openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "program build/main.elf verify reset exit"
# openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "program build/main.elf verify reset"
