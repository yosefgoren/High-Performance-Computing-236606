#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 1 - Calculate Mandelbrot area - parallel padding
echo "########## Compiling your parallel padding code"
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/mandel_parallel_padding -fopenmp mandel_parallel_padding.c
echo "########## Executing your parallel padding code"
./bin/mandel_parallel_padding
echo "########## Done parallel padding"
