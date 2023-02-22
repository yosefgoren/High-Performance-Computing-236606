#!/bin/bash
#SBATCH -N 1 -p gpua100 --exclusive --time=5

module purge
module load gnu/10.2.0

NAME=parallel_cpu

rm -f $NAME
echo starting to compile
gcc -v
gcc -o $NAME -fopenmp -O2 -lm $NAME'_jacobi.c' mm_utils.c
if [ $? -eq 0 ]; then
	echo starting run
	./$NAME
	echo finished run
else
	echo compilation failed
fi