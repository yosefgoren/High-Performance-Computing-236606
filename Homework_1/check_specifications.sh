#!/bin/bash
/bin/echo "##" $(whoami) is checking specifications of a standard CPU Intel DevCloud node
echo "########################################### lscpu:"
lscpu
echo "########################################### cat /proc/cpuinfo:"
cat /proc/cpuinfo
echo "########################################### cat /proc/meminfo:"
cat /proc/meminfo
echo "########################################### numactl --hardware"
numactl --hardware
exit

