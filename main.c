#include "bus_network.h"
#include "useful.h"



/*

TODO
1. build bus route graph
2. implement dijkstras on graph
3. request bus times 

*/



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

    
    read_file(num_busstops, "bus_data/names.txt", &busstop_names, 1);
    read_file(num_busstops, "bus_data/location_n.txt", &location_n, 0);
    read_file(num_busstops, "bus_data/location_e.txt", &location_e, 0);
    read_file(len_routes, "bus_sequences/route.txt", &routes, 0);
    read_file(len_routes, "bus_sequences/sequence.txt", &sequences, 0);
    read_file(len_routes, "bus_sequences/stop_name.txt", &busstop_names_routes, 1);

    printf("\n\nbusstop names: \n");
    for (int i=0; i < num_busstops; i++ ) {
        printf("%s \n", busstop_names[i]); 
    }

    bucket * busstop_hashtable[DICT_SIZE];
    for (int i=0; i < DICT_SIZE; i++) {
        busstop_hashtable[i] = NULL;
    }

    int h = 0; 
    for (int i=0; i < num_busstops; i++) {  
        bus_stop *bs = malloc(sizeof(bus_stop));
        bs->northing = atoi(location_n[i]);
        bs->easting = atoi(location_e[i]);
        bs->name = busstop_names[i];
        bucket * buck = malloc(sizeof(bucket));
        buck->b = bs;
        buck->next = NULL;
        h = hash(bs->name, DICT_SIZE, MAX_WORD);

        if (busstop_hashtable[h] == NULL) {
            busstop_hashtable[h] = buck;
        } else {
            append_to_bucket(busstop_hashtable[h], buck);
        }
        
    }
    // print_dict(busstop_hashtable, DICT_SIZE);


    // char * nonmatching_busstops[30000];
    printf("YO1\n");
    list * nonmatching_busstops = malloc(sizeof(list));
    // list nonmatching_busstops;
    
    printf("YO2\n");
    nonmatching_busstops->next = NULL;
    printf("YO3\n");
    strcpy(nonmatching_busstops->s, "...");
    printf("YO2\n");
    int j=0;

    for (int i=0; i < len_routes; i++) {
        h = hash(busstop_names_routes[i], DICT_SIZE, MAX_WORD);
        bucket * boocket = busstop_hashtable[h];
        char * s = busstop_names_routes[i]; 

        printf("busstop_names_routes[i]: %s\n" ,busstop_names_routes[i]);
        printf(" h: %i \n", h);



        // bus_stop * busstooop = boocket->b;
        if (boocket == NULL) {
            // printf("j: %i \n", j);
            // strcpy(nonmatching_busstops[j],busstop_names_routes[i]);
            printf("YOOOOO\n");
            append_list(nonmatching_busstops, busstop_names_routes[i]);
            // printf("YObutasdasdqasdasdch\n");
            j++;
        }
        else {
            int dasf = 0;
            // printf("%s \n\n\n", boocket->b->name);
        }
        // bucket * b = find_in_bucket(boocket, s);
        // append_buses(b->b->bus_list, atoi(routes[i]));
    }

    print_list(nonmatching_busstops);

    printf("YO");


    // printf("\n\nnon matching strings: \n");
    // for (int i=0; i < j; i++) {
    //     printf(" %s\n", nonmatching_busstops[i]);
    // }



    // print_busstops(busstop_hashtable, DICT_SIZE);




    free(nonmatching_busstops);
}