#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#compile with default compiler optimizations (feel free to add your own flags to achieve better performance!)
rm -f ./bin/*
icx -qopenmp -fopenmp-targets=spir64 -O2 gput.c -o ./bin/heat_gpu.out
if [ ! -z $? ];
then
    exit 1
fi
./bin/heat_gpu.out


