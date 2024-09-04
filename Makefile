dependencias = lib/server_functions.c lib/log.c

all: servidor

servidor: main.o lib/server_functions.o lib/log.o
	gcc -o servidor main.o lib/server_functions.o lib/log.o

main.o: main.c
	gcc -c -o main.o main.c

lib/server_functions.o: lib/server_functions.c
	gcc -c -o lib/server_functions.o lib/server_functions.c

lib/log.o: lib/log.c
	gcc -c -o lib/log.o lib/log.c

clean:
	rm -f main.o lib/*.o servidor
