#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

icc -O3 -fopenmp -qopt-report=5 -qopt-report-phase=vec pi.c fx.c -o ./bin/openmp_simd_pi -xCORE-AVX512 -qopt-zmm-usage=high
./bin/openmp_simd_pi


