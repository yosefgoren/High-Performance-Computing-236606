#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
icxs -o bin/GS_tasks_blocks_parallel -O0 -fopenmp GS_tasks_blocks_parallel.c 
./bin/GS_tasks_blocks_parallel

