#!/bin/bash
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/matmul_parallel -O0 -fopenmp matmul_parallel.c 
./bin/matmul_parallel

