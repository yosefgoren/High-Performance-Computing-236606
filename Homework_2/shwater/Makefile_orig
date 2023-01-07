CC = icx
CFLAGS = -O0 -fopenmp

SRC_serial = vtk_export.c shwater2d_serial.c
SRC_parallel = vtk_export.c shwater2d_parallel.c
OBJS_serial = ${SRC_serial:.c=.o}
OBJS_parallel = ${SRC_parallel:.c=.o}
DEST_serial = bin/shwater2d_serial
DEST_parallel = bin/shwater2d_parallel
all: $(DEST_serial) $(DEST_parallel)

$(DEST_serial): $(OBJS_serial)
	$(CC) $(CFLAGS) $(OBJS_serial) -o $@ -lm	

$(DEST_parallel): $(OBJS_parallel)
	$(CC) $(CFLAGS) $(OBJS_parallel) -o $@ -lm	

clean:
	rm -f $(DEST_serial) *.o
	rm -f $(DEST_parallel) *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<