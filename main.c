#include "bus_network.h"
#include "useful.h"



/*

TODO
1. build bus route graph
2. implement dijkstras on graph
3. request bus times 

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
    

    int emp = 0;
    int nemp = 0;
    int num_notfound;

    for (int i=0; i < len_routes; i++) {
        h = hash(busstop_names_routes[i], DICT_SIZE, MAX_WORD);
        bucket * boocket = busstop_hashtable[h];
        char * s = busstop_names_routes[i]; 
        int status = 0;


        if (boocket == NULL) {
            emp++;
        }
        
        else {

            printf("\ni: %i\n", i);            
            bucket * buk = malloc(sizeof(bucket));

            status = find_in_bucket(&boocket, busstop_names_routes[i], atoi(routes[i]));
            
            if (status == 1) {
                exit(1);
            } else if (status == 2) {
                num_notfound++;
            }

            
            // if (buk == NULL) {
            //     printf("buk == NULL, print bucket:\n");
            //     print_bucket(boocket);
            //     emp++;
            //     continue;
            // }
            
            nemp ++;
            // free(buk);


        }
    }



    // num empty not useful anymore, using num_notfound instead !!
    // printf("END\n");
    // printf("num empty:  %i \n", emp);
    // printf("num not empty:  %i \n\n\n", nemp);


    for (int n = 0; n < 1500; n++) {
        if (busstop_hashtable[n] != NULL ) {
            
            printf("%s:  ", busstop_hashtable[n]->b->name);
            for (int p=0; p < 20; p++) {
                printf("\t%i", busstop_hashtable[n]->b->bus_list[p]);
            }

        printf("\n");   

        }
    }


    printf("\n\n num notfound: %i\n\n", num_notfound);
}