CC = gcc
CFLAGS = -g -std=c99 -Wall -Wvla -Werror -fsanitize=address,undefined

OBJS = estimate.o matrix_functions.o

estimate: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

estimate.o: estimate.c matrix_functions.h
	$(CC) $(CFLAGS) -c main.c

matrix_functions.o: matrix_functions.c matrix_functions.h
	$(CC) $(CFLAGS) -c matrix_functions.c

clean:
	rm -rf estimate $(OBJS) *.dSYM
