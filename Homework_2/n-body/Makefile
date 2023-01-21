FLAGS=-openmp -O3
CC=icx

NAME?=n-body

all:
	$(CC) -o body_linear $(FLAGS) $(NAME)_body_linear.c
	$(CC) -o serial $(FLAGS) $(NAME)_serial.c

#$(CC) -o dim_linear $(FLAGS) $(NAME)_dim_linear.c
clean:
	del *.exe
