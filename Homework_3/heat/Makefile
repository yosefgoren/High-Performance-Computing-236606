FLAGS=-fopenmp -O3
LIBS=-lm
CC=gcc

# t:
# 	$(CC) -o t.exe $(FLAGS) gput.c 

# specify the target to openmp:
# 

parallel_gpu: parallel_gpu_heat.c
	$(CC) -v -o $@ $(FLAGS) -fopenmp-targets=spir64 $(LIBS) $^
parallel_cpu: parallel_cpu_heat.c
	$(CC) -o $@ $(FLAGS) $(LIBS) $^
serial: serial_heat.c
	$(CC) -o $@ $(FLAGS) $(LIBS) $^
	
clean:
	del *.exe
