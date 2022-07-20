

# compiler:
CC = gcc

# compiler flags: 
CFLAGS  = -g -Wall

# the build target executable:
TARGET = main

# object files to build:
OBJ = main.o bus_network.o useful.o shortest_path.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)