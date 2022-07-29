#include "bus_network.h"
#include "useful.h"
#include "shortest_path.h"
#include <time.h>


// changed one of MOORGATE STATION to LONDON WALL / MOORGATE STATION (next to LONDON WALL / MUSEUM OF LONDON for 100 bus) 

/*
TODO

1. make python script to request bus times for all bus routes, parse the json and write
    relevant info into text file 
2. read the text file in main.c and construct graph (step 3.)
3. pre compute edge times using api: https://api.tfl.gov.uk/line/2/arrivals (python) for each bus route
    since live bus predictions use same estimate (doesn't take traffic etc into account)
4. convert target locatino into a coordinate

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

    bus_stop * busstop_array[num_busstops];

    

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
        if (strcmp(bs->name, "BUSH ROAD") == 0) {
            printf("\n BUSH ROAD FOUND");
            
        }

        busstop_array[i] = bs;
        

        for (int n=0; n< 10; n++) {
            (bs->bus_list)[n] = 0; // init array of buses at busstop to 0s
        }
        

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


    


    
    for (int n = 0; n < 10; n++) {
        if (busstop_hashtable[n] != NULL ) {
            printf("%s:  ", busstop_hashtable[n]->b->name);
            for (int p=0; p < 20; p++) {
                printf("\t%i", busstop_hashtable[n]->b->bus_list[p]);
            }
        printf("\n");   
        }
    }



    // int num1stops = 28;
    // char * arrival_mins[num1stops];

    // read_file(num1stops, "data_processing/bus_times/1dt.txt", &arrival_mins, 0);


    neighbour* bus_graph[num_busstops]; // adjacency list 

    for (int i=0; i < num_busstops; i ++ ) {
        bus_graph[i] = NULL;
    }



    int j=0;
    
    // while (j < 58072) {
    while (j < 5000){

        printf("\nroutei %s", routes[j]);
        
        int num_busj = 0;
        while (atoi(sequences[j+num_busj+1]) > atoi(sequences[j+num_busj])) {
            num_busj ++;
        }
        
        // printf("\nj %i\n", j);

        char s[100] = "data_processing/bus_times/";
        strcat(s, routes[j]);
        strcat(s, "dt.txt");
        printf("\n%s ", s);

        // char * arrival_mins[num_busj];
        // read_file(num_busj, s, &arrival_mins, 0);


        // build graph

        srand( time(NULL) );
        

        for (int i=j; i < j+num_busj; i ++ ) { // do 1 bus only first

                int h = hash(busstop_names_routes[i], DICT_SIZE, MAX_WORD);
                int hnext = hash(busstop_names_routes[i+1], DICT_SIZE, MAX_WORD);
                bucket * buk = busstop_hashtable[h];
                bucket * buknext = busstop_hashtable[hnext];

                
                // printf("\n %s --> %s",busstop_names_routes[i], busstop_names_routes[i+1]);
                int id = add_neighbour(bus_graph, &buk, &buknext, routes[i], 1.5, busstop_names_routes[i], busstop_names_routes[i+1]);            
                if (id == -2 && i != j+num_busj-1) {
                    hnext = hash(busstop_names_routes[i+2], DICT_SIZE, MAX_WORD);
                    buknext = busstop_hashtable[hnext];
                    id = add_neighbour(bus_graph, &buk, &buknext, routes[i], 1.5, busstop_names_routes[i], busstop_names_routes[i+2]);
                    i++;
                }
                
                // printf("neighbour->node->name %s\n",(bus_graph[id])->node->name);
                // printf("id %i\n", id);

        }   

        j += num_busj + 1;
        


    }

    printf("END\n");

    /*

    PROBLEMS:
     1. SOME BUS STOP NAMES ARE NOT UNIQUE I.E. THERE'S BUS STOPS IN DIFFERENT LOCATIONSN W/ SAME NAME
        SO E.G. 'BUSH ROAD' EXISTS BOTH IN NORTH LONDON AND NEXT TO CANADA WATER SO DIJKSTRAS
        THINKS THERE'S A LINK BETWEEN THE TWO AND TAKES A BUS TO NORTH LONDON THEN TELEPORTS NEXT TO CANADA WATER...
        (WHEN J < 5000)
    2. IN NAMES EACH BUS STOP APPEARS AT LEAST TWICE, 1 FOR EACH DIRECTION. BUT IN MY CODE IT'S IMPLEMENTED SO
        BOTH DIRECTIONS ARE REPRESENTED AT 1 BUS STOP (NOT TWO FOR EACH SIDE OF THE ROAD) SO NEED TO DELETE THE SECOND ONE
            !! BE CAREFUL NOT TO DELETE BUS STOP WITH SAME NAME BUT DIFFERENT LOCATION THO .... NEED TO CHECK IF THE NAMES
            CORRESPOND TO SAME EASTING & NORTHING !!
    */


    // int surrey_quays_id = 9471;

    // neighbour * sq = bus_graph[surrey_quays_id];
    // printf("\n\n\n\n surrey quays neighbours:   ");
    // while (sq != NULL) {
    //     printf(" %s,", sq->node->name);
    //     sq = sq->next;
    // }
    // printf("\n\n");

    dijkstras(530000, 181430, 535460, 179490, bus_graph, busstop_array, num_busstops);

}