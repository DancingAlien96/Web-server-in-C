CC = gcc
CFLAGS = -Wall -Wextra

all: servidor

servidor: main.c lib/server_functions.c
	$(CC) $(CFLAGS) -o servidor main.c lib/server_functions.c

clean:
	rm -f servidor

