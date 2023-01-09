FLAGS=-openmp -Od -Wno-deprecated
CC=icx

NAME?=shwater2d

all:
	$(CC) -o parallel $(FLAGS) $(NAME)_parallel.c vtk_export.c
	$(CC) -o serial $(FLAGS) $(NAME)_serial.c vtk_export.c

clean:
	del *.exe
