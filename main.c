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
    
    int len_routes = 58073;
    char *routes[len_routes];
    char *sequences[len_routes];
    char *busstop_names_routes[len_routes];

    

    read_file(num_busstops, "bus_data/names.txt", &busstop_names);
    read_file(num_busstops, "bus_data/location_n.txt", &location_n);
    read_file(num_busstops, "bus_data/location_e.txt", &location_e);

    read_file(len_routes, "bus_sequences/route.txt", &routes);
    read_file(len_routes, "bus_sequences/sequence.txt", &sequences);
    read_file(len_routes, "bus_sequences/stop_name.txt", &busstop_names_routes);

    bucket * busstop_hashtable[DICT_SIZE];
    for (int i=0; i < DICT_SIZE; i++) {
        busstop_hashtable[i] = NULL;
    }

    int h = 0; 
    for (int i=0; i < num_busstops; i++) {  
        bus_stop *b = malloc(sizeof(bus_stop));
        b->northing = atoi(location_n[i]);
        b->easting = atoi(location_e[i]);
        b->name = busstop_names[i];
        h = hash(b->name, DICT_SIZE, MAX_WORD);
        if (busstop_hashtable[h] == NULL) {
            busstop_hashtable[h] = b;
        } else {
            append_to_bucket(busstop_hashtable[h], b);
        }
        
    }
    print_dict(busstop_hashtable, DICT_SIZE);


    for (int i=0; i < len_routes; i++) {
        h = hash(busstop_names_routes[i], DICT_SIZE, MAX_WORD);

        // busstop_hashtable[h];

    }
}