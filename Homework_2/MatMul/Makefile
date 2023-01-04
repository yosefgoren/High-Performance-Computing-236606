FLAGS=-openmp -Od -Qxcore-avx512
CC=icx

all: serial parallel


serial: matmul_serial.c
	icx -o $@ $(FLAGS) $^

parallel: matmul_parallel.c
	icx -o $@ $(FLAGS) $^

clean:
	del *.exe