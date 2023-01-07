# BINS=-L"C:\Program Files (x86)\Intel\oneAPI\compiler\2022.2.1\windows\compiler\lib\intel64_win"
FLAGS=-openmp -O3
CC=icx

all: serial parallel


serial: matmul_serial.c
	$(CC) -o $@ $(FLAGS) $^

parallel: matmul_parallel.c
	$(CC) -o $@ $(FLAGS) $^

clean:
	del *.exe