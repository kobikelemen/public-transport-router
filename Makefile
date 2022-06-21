

CC=clang 

all: main

bus_network.o: bus_network.h bus_network.c
	$(CC) $(CLFLAGS) -c bus_network.c 

useful.o: useful.h useful.c 
	$(CC) $(CLFLAGS) -c useful.c 

main: bus_network.o useful.o main.c
	$(CC) $(CLFLAGS) -o main main.c bus_network.o useful.o

