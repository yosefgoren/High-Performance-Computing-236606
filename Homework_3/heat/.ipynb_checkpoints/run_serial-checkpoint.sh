#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#compile with default compiler optimizations (feel free to add your own flags to achieve better performance!)
icc -O2 -fopenmp serial_heat.c -o ./bin/serial_heat.out
./bin/serial_heat.out


