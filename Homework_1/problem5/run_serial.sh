#!/bin/bash
/bin/echo "##" $(whoami) is running HW1 Problem 5 - Prime Numbers 
echo "########## Compiling the parallel code"
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx -o bin/prime_parallel_schedule -fopenmp prime_count_serial.c
echo "########## Executing the parallel code"
./bin/prime_parallel_schedule
echo "########## Done parallel"

