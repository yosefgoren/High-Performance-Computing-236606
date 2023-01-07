FLAGS=-openmp -O3
CC=icx

NAME?=n-body

all:
	$(CC) -o body_linear $(FLAGS) $(NAME)_body_linear.c
	$(CC) -o nested $(FLAGS) $(NAME)_nested.c
	$(CC) -o dim_linear $(FLAGS) $(NAME)_dim_linear.c
	$(CC) -o serial $(FLAGS) $(NAME)_serial.c

clean:
	del *.exe

#float* deltas = (float*)malloc(sizeof(float)*N_BODIES*N_BODIES*N_DIMS);