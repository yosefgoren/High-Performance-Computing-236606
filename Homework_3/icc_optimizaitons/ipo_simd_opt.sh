#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#edit this compilation line to include ipo and simd extensions
icc -O2 -qopt-report=5 -qopt-report-phase=vec pi.c fx.c -o ./bin_ipo_simd_opt/openmp_simd_pi
./bin_ipo_simd_opt/openmp_simd_pi


