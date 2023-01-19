#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#compile without any optimizations
icc -O0 pi.c fx.c -o ./bin_no_opt/O0_pi
./bin_no_opt/O0_pi


