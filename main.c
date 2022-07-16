#include "bus_network.h"
#include "useful.h"



/*

TODO

1. make python script to request bus times for all bus routes, parse the json and write
    relevant info into text file 
2. read the text file in main.c and construct graph (step 3.)
3. pre compute edge times using api: https://api.tfl.gov.uk/line/2/arrivals (python) for each bus route
    since live bus predictions use same estimate (doesn't take traffic etc into account)
4. convert target locatino into a coordinate

1. build bus route graph
2. implement dijkstras on graph
3. request bus times 
 PROBLEM... many bus routes are strings not numbers so find_in_bucket doesn't find them e.g. N2 bus

*/


/*
Don't bother with walking graph, instead first estimate walking distance based on
actual distance to find nearest stations then use google maps api to get actual 
walking distance to station
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

    bucket * busstop_hashtable[DICT_SIZE];

    

    for (int i=0; i < DICT_SIZE; i++) {
        busstop_hashtable[i] = NULL;
    }
    int bytes = 0;

    int h = 0; 
    for (int i=0; i < num_busstops; i++) {  
        // init bus stop
        bus_stop *bs = malloc(sizeof(bus_stop));
        bs->northing = atoi(location_n[i]);
        bs->easting = atoi(location_e[i]);
        bs->name = busstop_names[i];
        bs->id = i;
        // buses * buslist = malloc(sizeof(buses));
        // buslist = NULL;
        // bs->bus_list = buslist;

        for (int n=0; n< 10; n++) {
            (bs->bus_list)[n] = 0; // init array of buses at busstop to 0s
        }
        //

        // init bucket which holds bus stop
        bucket * buck = malloc(sizeof(bucket));
        bytes += sizeof(bucket);
        buck->b = bs;
        buck->next = NULL;
        //
        h = hash(bs->name, DICT_SIZE, MAX_WORD);

        if (busstop_hashtable[h] == NULL) {
            busstop_hashtable[h] = buck;
        } else {
            append_to_bucket(busstop_hashtable[h], buck);
        }
        
    }


    int num_1 = 110;
    char * bus1[num_1];
    char bus_nums[num_1][1];
    char arrival_mins[num_1][2];
    char bsnames[num_1][50];

    read_file(num_1, "data_processing/bus_times/1.txt", &bus1, 0);

    for (int i=0; i < num_1; i ++) {
        memcpy(bus_nums[i], &(bus1[i][0]), sizeof(*(bus1[i])));
        memcpy(arrival_mins[i], &(bus1[i][4]), 2 * sizeof(*(bus1[i])) );
        memcpy(bsnames[i], &(bus1[i][10]), (strlen(bus1[i]) - 10) * sizeof(*(bus1[i])));        
        printf("\nroute: %i", atoi(bus_nums[i]));
        printf("\nmins: %i", atoi(arrival_mins[i]));
        printf("\nname:%s", bsnames[i]);
    }


    neighbour* bus_graph[num_busstops]; // adjacency linked 

    int num_notfound;
    int hnext;

    int max = 56;

    for (int i=0; i < max; i++) {
        h = hash(busstop_names_routes[i], DICT_SIZE, MAX_WORD);
        bucket * boocket = busstop_hashtable[h];
        int status = 0;

        if (i < max-1) {
            hnext = hash(busstop_names_routes[i+1], DICT_SIZE, MAX_WORD);
            bucket * boocketnext = busstop_hashtable[hnext];

        }

        if (boocket == NULL) {
            continue;
        } else {
            bucket * buk = malloc(sizeof(bucket));
            status = find_in_bucket(&boocket, busstop_names_routes[i], atoi(routes[i]));
            
            if (status == 2) {
                num_notfound++;
            }
           
        }
    }


    for (int n = 0; n < 10; n++) {
        if (busstop_hashtable[n] != NULL ) {
            
            printf("%s:  ", busstop_hashtable[n]->b->name);
            for (int p=0; p < 20; p++) {
                printf("\t%i", busstop_hashtable[n]->b->bus_list[p]);
            }
        printf("\n");   
        }
    }


    printf("\n\n num notfound: %i\n\n", num_notfound);

    
    

    // int h;
    // for (int i=0; i < 56; i ++ ) { // do 1 bus only first
    //     h = hash()
    // }



}