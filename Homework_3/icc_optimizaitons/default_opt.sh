#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#compile with default compiler optimizations + print detailed reports
icc -O2 -qopt-report=5  -qopt-report-phase=vec pi.c fx.c -o ./bin_default_opt/O2_pi
./bin_default_opt/O2_pi


