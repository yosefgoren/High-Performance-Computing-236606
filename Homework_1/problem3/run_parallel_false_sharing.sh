#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 1 - Calculate Mandelbrot area - parallel false_sharing
echo "########## Compiling your parallel false_sharing code"
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/mandel_parallel_false_sharing -fopenmp mandel_parallel_false_sharing.c
echo "########## Executing your parallel false_sharing code"
./bin/mandel_parallel_false_sharing
echo "########## Done parallel false_sharing"
