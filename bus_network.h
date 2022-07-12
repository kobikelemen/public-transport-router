
#ifndef BUS_NETWORK
#define BUS_NETWORK

#include <stdlib.h>
#include <stdio.h>
#include <string.h>





// linked list of buses at a busstop
typedef struct buses
{
    int bus;
    struct buses * next;
} buses;





// node of busstop graph
typedef struct bus_stop 
{
    char * name; 
    // struct buses * bus_list;
    int bus_list[10];
    struct bus_stop * neighbour;
    int northing;
    int easting;
} bus_stop;


// add to linked list
void append_buses(bus_stop **busstop, int bus);
void print_buses_at_busstop(int bu[], int arrsize);


// distance between bustops based on northing and easting
float dist_busstops(int coords1, int coords2); //   not implemented yet


// bus stop graph
typedef struct bus_network
{
    int num_busstops;
    struct bus_stop* busstops[];
} bus_network;



// hash table for bus stops
typedef struct bucket
{
    struct bus_stop *b;
    struct bucket *next;
} bucket;


int hash(char name[], int DICT_SIZE, int MAX_WORD);
void print_bucket(bucket* b);
void print_dict(bucket * hash_table[], int DICT_SIZE);
void append_to_bucket(bucket * b, bucket * a);
bucket * find_in_bucket(bucket ** b, char * busstop_name, int add_busroute);
void print_busstops(bucket * hashtable[], int DICT_SIZE);

#endif 