#include "bus_network.h"
#include "useful.h"



int main()
{

    int MAX_WORD = 256;
    int DICT_SIZE = 20000;

    int num_busstops = 18951;
    char *busstop_names[num_busstops];
    char *location_n[num_busstops];
    char *location_e[num_busstops];

    bucket * busstop_hashtable[DICT_SIZE];

    read_file(num_busstops, "bus_data/names.txt", &busstop_names);
    read_file(num_busstops, "bus_data/location_n.txt", &location_n);
    read_file(num_busstops, "bus_data/location_e.txt", &location_e);

    struct bus_stop *busstops[num_busstops];

    for (int i=0; i < num_busstops; i++) {  
        bus_stop *b = malloc(sizeof(bus_stop));
        b->northing = atoi(location_n[i]);
        b->easting = atoi(location_e[i]);
        b->name = busstop_names[i];
        // busstops[i] = b;
        int h = hash(b->name, DICT_SIZE, MAX_WORD);
        busstop_hashtable[h] = b;
    }
    print_dict(busstop_hashtable, DICT_SIZE);
}