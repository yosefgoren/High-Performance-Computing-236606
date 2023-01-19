#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#compile with default compiler optimizations (feel free to add your own flags to achieve better performance!)
icc -O2 -fopenmp serial_jacobi.c mm_utils.c mm_utils.h -o ./bin/serial_jacobi.out
./bin/serial_jacobi.out


