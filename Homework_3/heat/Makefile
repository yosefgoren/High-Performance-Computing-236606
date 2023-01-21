FLAGS=-fopenmp -O0
CC=clang

t:
	$(CC) -o t.exe $(FLAGS) gput.c 

all:
	$(CC) -o gpuimp $(FLAGS) parallel_gpu_heat.c


clean:
	del *.exe
