#!/bin/bash
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
make bin/shwater2d_serial
./bin/shwater2d_serial

