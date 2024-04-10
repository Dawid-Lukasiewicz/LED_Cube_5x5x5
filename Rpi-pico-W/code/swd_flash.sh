#!/usr/bin/bash

# Run the script with sudo
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program build/main.elf verify reset exit"
# openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program build/main.elf verify reset"
