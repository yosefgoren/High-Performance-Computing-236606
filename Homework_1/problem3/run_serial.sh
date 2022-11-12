#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 1 - Calculate Mandelbrot area - serial
echo "########## Compiling the given serial code"
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/mandel_serial -fopenmp mandel_serial.c
echo "########## Executing the given serial code"
./bin/mandel_serial
echo "########## Done serial"

