#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 1 - Calculate Mandelbrot area - parallel reduction
echo "########## Compiling your parallel reduction code"
icx -o bin/mandel_parallel_reduction -fopenmp mandel_parallel_reduction.c
echo "########## Executing your parallel reduction code"
./bin/mandel_parallel_reduction
echo "########## Done parallel reduction"
