#!/bin/bash
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/matmul_serial -O0 -fopenmp matmul_serial.c 
./bin/matmul_serial

