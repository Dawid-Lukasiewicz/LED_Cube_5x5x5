#!/usr/bin/bash

openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program build/main.elf verify reset exit"
# openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program build/main.elf verify reset"
