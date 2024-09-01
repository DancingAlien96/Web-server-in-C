dependencias = lib/server_functions.c lib/log.c

all: servidor

servidor: main.o server_functions.o log.o
	gcc -o servidor main.o server_functions.o log.o

main.o: main.c
	gcc -c -o main.o main.c

server_functions.o: lib/server_functions.c
	gcc -c -o server_functions.o lib/server_functions.c

log.o: lib/log.c
	gcc -c -o log.o lib/log.c

clean:
	rm -f *.o servidor
