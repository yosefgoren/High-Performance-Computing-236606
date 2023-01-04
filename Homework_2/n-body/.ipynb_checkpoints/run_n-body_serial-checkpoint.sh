#!/bin/bash
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icx n-body_serial.c -fopenmp -lm -O0 -o ./bin/n-body_serial  
./bin/n-body_serial

