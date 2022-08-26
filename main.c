#include "bus_network.h"
#include "useful.h"
#include "shortest_path.h"
#include <time.h>



int main(int argc, char **argv)
{

    int starte;
    int startn;
    int ende;
    int endn;
    
    if (argc > 1) {
        starte = atoi(argv[1]);
        startn = atoi(argv[2]);
        ende = atoi(argv[3]);
        endn = atoi(argv[4]);
    } else {
        starte = 527278;
        startn = 176916;
        ende = 531917;
        endn = 172263;
    }
    
    

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
    char *seq_location_n[len_routes];
    char *seq_location_e[len_routes];
    
    read_file(num_busstops, "bus_data/names.txt", &busstop_names, 1);
    read_file(num_busstops, "bus_data/location_n.txt", &location_n, 0);
    read_file(num_busstops, "bus_data/location_e.txt", &location_e, 0);
    read_file(len_routes, "bus_sequences/route.txt", &routes, 0);
    read_file(len_routes, "bus_sequences/sequence.txt", &sequences, 0);
    read_file(len_routes, "bus_sequences/stop_name.txt", &busstop_names_routes, 1);
    read_file(len_routes, "bus_sequences/seq_location_n.txt", &seq_location_n, 0);
    read_file(len_routes, "bus_sequences/seq_location_e.txt", &seq_location_e, 0);

    bucket * busstop_hashtable[DICT_SIZE];
    bus_stop * busstop_array[num_busstops];

    for (int i=0; i < DICT_SIZE; i++) {
        busstop_hashtable[i] = NULL;
    }
    int bytes = 0;
    int h = 0; 
    for (int i=0; i < num_busstops; i++) {  
        bus_stop *bs = malloc(sizeof(bus_stop));
        bs->northing = atoi(location_n[i]);
        bs->easting = atoi(location_e[i]);
        bs->name = busstop_names[i];
        bs->id = i;
        busstop_array[i] = bs;
        for (int n=0; n< 10; n++) {
            (bs->bus_list)[n] = 0;
        }
        bucket * buck = malloc(sizeof(bucket));
        bytes += sizeof(bucket);
        buck->b = bs;
        buck->next = NULL;

        h = hash(bs->name, DICT_SIZE, MAX_WORD);
        if (busstop_hashtable[h] == NULL) {
            busstop_hashtable[h] = buck;
        } else {
            append_to_bucket(busstop_hashtable[h], buck);
        }
    }


    neighbour* bus_graph[num_busstops]; // adjacency list 

    for (int i=0; i < num_busstops; i ++ ) {
        bus_graph[i] = NULL;
    }

    int j=0;
    while (j < 41228){
        int num_busj = 0;
        while (atoi(sequences[j+num_busj+1]) > atoi(sequences[j+num_busj])) {
            num_busj ++;
        }

        char s[100] = "data_processing/bus_times/";
        strcat(s, routes[j]);
        strcat(s, "dt.txt");
        
        // build graph
        srand( time(NULL) );
        for (int i=j; i < j+num_busj; i ++ ) {

                int h = hash(busstop_names_routes[i], DICT_SIZE, MAX_WORD);
                int hnext = hash(busstop_names_routes[i+1], DICT_SIZE, MAX_WORD);
                bucket * buk = busstop_hashtable[h];
                bucket * buknext = busstop_hashtable[hnext];
                int id = add_neighbour(
                    bus_graph, &buk, &buknext, routes[i], 1.5, busstop_names_routes[i], busstop_names_routes[i+1],
                     atoi(seq_location_n[i]), atoi(seq_location_e[i]), atoi(seq_location_n[i+1]), atoi(seq_location_e[i+1])
                     );    
                if (id == -2 && i != j+num_busj) {
                    hnext = hash(busstop_names_routes[i+2], DICT_SIZE, MAX_WORD);
                    buknext = busstop_hashtable[hnext];
                    id = add_neighbour(
                        bus_graph, &buk, &buknext, routes[i], 1.5, busstop_names_routes[i], busstop_names_routes[i+2],
                        atoi(seq_location_n[i]), atoi(seq_location_e[i]), atoi(seq_location_n[i+2]), atoi(seq_location_e[i+2])
                        );
                    i++;
                }
        }   
        j += num_busj + 1;

    }

    dijkstras(starte, startn, ende, endn, bus_graph, busstop_array, num_busstops);

}