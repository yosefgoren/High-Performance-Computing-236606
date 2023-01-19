#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#compile with default compiler optimizations (feel free to add your own flags to achieve better performance!)
icx -qopenmp -fopenmp-targets=spir64 -O2 parallel_gpu_jacobi.c mm_utils.c mm_utils.h -o ./bin/jacobi_gpu.out
./bin/jacobi_gpu.out


