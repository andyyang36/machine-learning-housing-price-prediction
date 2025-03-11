CC = gcc
CFLAGS = -g -std=c99 -Wall -Wvla -Werror -fsanitize=address,undefined

OBJS = main.o matrix_functions.o

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c matrix_functions.h
	$(CC) $(CFLAGS) -c main.c

matrix_functions.o: matrix_functions.c matrix_functions.h
	$(CC) $(CFLAGS) -c matrix_functions.c

clean:
	rm -rf main $(OBJS) *.dSYM
