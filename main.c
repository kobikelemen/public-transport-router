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
    // print_dict(busstop_hashtable, DICT_SIZE);


    // char * nonmatching_busstops[30000];
    list * nonmatching_busstops = malloc(sizeof(list));
    
    
    nonmatching_busstops->next = NULL;
        
    int emp = 0;
    int nemp = 0;

    for (int i=0; i < len_routes; i++) {
        h = hash(busstop_names_routes[i], DICT_SIZE, MAX_WORD);
        bucket * boocket = busstop_hashtable[h];
        char * s = busstop_names_routes[i]; 

        // printf("busstop_names_routes[i]: %s\n" ,busstop_names_routes[i]);
        // printf(" h: %i \n", h);



        // bus_stop * busstooop = boocket->b;
        if (boocket == NULL) {
            // printf("j: %i \n", j);
            // strcpy(nonmatching_busstops[j],busstop_names_routes[i]);
            // printf("boocket = NULL!\n");
            // printf("i: %i \n", i);
            // printf("busstop_names_routes[i]: %s\n" ,busstop_names_routes[i]);
            // append_list(nonmatching_busstops, busstop_names_routes[i]);
            emp++;
        }
        else {

            // printf("test %s \n",boocket->b->name);
            printf("%i \n" ,(boocket->b->bus_list)[0]);

            
            bucket * buk = malloc(sizeof(bucket));

            buk = find_in_bucket(boocket, busstop_names_routes[i]);
            printf("\nMAIN - buk ptr: %p\n", buk);
            // printf("MAIN- bucket->b->name: %s \n", buk->b->name);
            
            if (buk == NULL) {
                emp++;
                continue;
            }
            printf("MAIN - print bucket \n");
            print_bucket(boocket);
            
            printf("\nYO\n");
            print_bucket(buk);

            if (buk->b == NULL) {
                printf("FAIL\n");
            }
            printf("printing bucket: \n");
            print_bucket(buk);

            append_buses(buk->b, atoi(routes[i]));
            nemp ++;
            free(buk);

        }
    }

    

    


    // printf("\n\nnon matching strings: \n");
    // for (int i=0; i < j; i++) {
    //     printf(" %s\n", nonmatching_busstops[i]);
    // }



    // print_busstops(busstop_hashtable, DICT_SIZE);
    // print_busstops(busstop_hashtable, 10);


    
    printf("END\n");

    printf("num empty:  %i \n", emp);
    printf("num not empty:  %i \n", nemp);


    free(nonmatching_busstops);
    // for (int i=0; i < DICT_SIZE; i++) {
    //     free(busstop_hashtable[i]);
    // }
}