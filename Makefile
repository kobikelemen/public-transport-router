

CC=clang

CFLAGS=-g

all: mainapp

mainapp: main.o bus_network.o useful.o
	$(CC) $(CFLAGS) main.o bus_network.o useful.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

bus_network.o: bus_network.c
	$(CC) $(CFLAGS) -c bus_network.c

useful.o: useful.c
	$(CC) $(CFLAGS) -c useful.c

clean:
	rm a.out *.o mainapp