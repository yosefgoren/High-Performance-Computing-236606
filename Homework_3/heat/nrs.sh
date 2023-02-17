#!/bin/bash
#SBATCH -N 1 -p gpua100 --exclusive --time=5

module purge
module load gnu/9.1.0

NAME=serial

rm -f $NAME
echo starting to compile
gcc -o $NAME -fopenmp -O3 -lm $NAME'_heat.c'
if [ $? -eq 0 ]; then
	echo starting run
	./$NAME
	echo finished run
else
	echo compilation failed
fi