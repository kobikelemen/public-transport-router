#include <stdlib.h>
#include <stdio.h>





// linked list of buses at a busstop
typedef struct buses
{
    int bus;
    buses * next;
} buses;


void append_buses(buses *bus_head, int bus)
{
    buses *b = malloc(sizeof(buses));
    b->bus = bus;
    bus_head->next = b;

}






// node of busstop graph
typedef struct bus_stop 
{
    char * name; 
    buses bus_list;
    bus_stop * neighbour;
    int coords[2];
} bus_stop;


float dist_busstops(int coords1, int coords2); // finds distance between busstops




// bus stop graph
typedef struct bus_network
{
    int num_busstops;
    bus_stop* busstops[];
} bus_network;

// tfl.gov.uk/tfl/syndication/feeds/bus-sequences.csv


int main()
{

    int num_busstops;
    for (int i=0; i < num_busstops; i++) {
        bus_stop *b = malloc(sizeof(bus_stop));
    }
}