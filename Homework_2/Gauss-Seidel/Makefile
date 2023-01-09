FLAGS=-openmp -Od -Wno-deprecated
CC=icx

NAME?=GS

all:
	$(CC) -o serial $(FLAGS) $(NAME)_serial.c
	$(CC) -o parallel $(FLAGS) $(NAME)_tasks_blocks_parallel.c

clean:
	del *.exe
