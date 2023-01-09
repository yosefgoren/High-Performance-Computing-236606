#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/LU_parallel -O0 -fopenmp LU_parallel.c 
./bin/LU_parallel


