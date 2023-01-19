#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

icc -O2 -fopenmp -qopt-report=5 -qopt-report-phase=vec pi.c fx.c -o ./bin/openmp_simd_pi
./bin/openmp_simd_pi


