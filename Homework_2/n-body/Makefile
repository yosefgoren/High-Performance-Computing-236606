FLAGS=-openmp -Od
CC=icx

NAME?=n-body

all:
	$(CC) -o parallel $(FLAGS) $(NAME)_parallel.c
	$(CC) -o serial $(FLAGS) $(NAME)_serial.c

clean:
	del *.exe