FLAGS=-openmp -Od -Qxcore-avx512
CC=icx

NAME?=LU

all: serial parallel


serial: $(NAME)_serial.c
	icx -o $@ $(FLAGS) $^

parallel: $(NAME)_parallel.c
	icx -o $@ $(FLAGS) $^

clean:
	del *.exe