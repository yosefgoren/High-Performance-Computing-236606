#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 1 - Calculate Mandelbrot area - parallel atomic
echo "########## Compiling your parallel atomic code"
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/mandel_parallel_atomic -fopenmp mandel_parallel_atomic.c
echo "########## Executing your parallel atomic code"
./bin/mandel_parallel_atomic
echo "########## Done parallel atomic"
