#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#compile with default compiler optimizations (feel free to add your own flags to achieve better performance!)
icx -qopenmp -fopenmp-targets=spir64 -O2 parallel_gpu_heat.c -o ./bin/heat_gpu.out
./bin/heat_gpu.out


