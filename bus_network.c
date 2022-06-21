#include "bus_network.h"


void append_buses(buses *bus_head, int bus)
{
    buses *b = malloc(sizeof(buses));
    b->bus = bus;
    bus_head->next = b;

}

// tfl.gov.uk/tfl/syndication/feeds/bus-sequences.csv
