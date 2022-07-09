#include "bus_network.h"



void append_buses(bus_stop *busstop, int bus)
{
    printf("YOO1\n");
    // buses *b = malloc(sizeof(buses));
    // b->bus = bus;
    // b->next = *bus_head;
    // *bus_head = b;

    int i=0; 
    while ((busstop->bus_list)[i] != 0) {
        printf("BI\n");
        printf(" cnt: %s\n", (busstop->bus_list)[i]);
        i++;
        if ( i > 1000 ) {
            break;
        }
    }
    printf("YOO2\n");
    printf("bus: %i\n", bus);
    printf(" cnt: %i\n", (busstop->bus_list)[i]);
    (busstop->bus_list)[i] = bus;



    // printf("YOO1\n");

    // if ((*bus_head) == NULL) {
    //     printf("ITS NULL BETCH \n");
    // }
    // printf("YOO4\n");

    // if ((*bus_head)->next == NULL) {
    //     printf("YOO2\n");
    //     buses *b = malloc(sizeof(buses));
    //     b->bus = bus;
    //     b->next = NULL;
    //     printf("YOO3\n");
    //     (*bus_head)->next = b;
    //     return;
    // }

    // append_buses(&((*bus_head)->next), bus);

}

void print_buses_at_busstop(buses * bu)
{
    if (bu == NULL) {
        return;
    }
    printf("%i ", bu->bus);
    print_buses_at_busstop(bu->next);
}


void print_busstops(bucket * hashtable[], int DICT_SIZE)
{
    for (int i=0; i < DICT_SIZE; i++) {
        printf("\n\n name: %s \n", hashtable[i]->b->name);
        printf("buses: ");
        print_buses_at_busstop(hashtable[i]->b->bus_list);
        printf("\n");
        // print neighbours to-do
        printf("northling: %i\n", hashtable[i]->b->northing);
        printf("easting: %i\n", hashtable[i]->b->easting);
    }
}




// hash table

int hash(char name[], int DICT_SIZE, int MAX_WORD)
{
    int length = strnlen(name, MAX_WORD);
    int hash_value = 0;
    for (int i=0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]);// % DICT_SIZE;
    }
    hash_value = abs(hash_value) % DICT_SIZE;
    return hash_value;
}

void print_bucket(bucket* buck)
{
    
    if (buck == NULL) {
        return;
    }
    
    printf("\t%s", buck->b->name);
    print_bucket(buck->next);
}

void print_dict(bucket * hash_table[], int DICT_SIZE)
{
    
    int len = DICT_SIZE;
    for (int i=0; i < len-2; i++) { // seg faults after hash_table[len-2] ...
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i", i);
            print_bucket(hash_table[i]);
            printf("\n");
        }
    }
    printf("\n\n");
}


void append_to_bucket(bucket * b, bucket * a)
{

    if (b->next == NULL) {
        b->next = a;
        return;
    }
    append_to_bucket(b->next, a);
}


// int is_in_bucket(bucket * buck,)


bucket * find_in_bucket(bucket * buk, char * busstop_name)
{
    
    // if ( strcmp(buk->b->name, "MUSEUM STREET") == 0) {
    //     return NULL;
    // }
    


    if (strcmp(buk->b->name, busstop_name) == 0) {
        printf("FIND_IN_BUCKET - buk ptr: %p\n", buk);
        printf("FIND_IN_BUCKET - print bucket: \n");
        print_bucket(buk);
        // printf("INSIDE FIND_IN_BUCKET- bucket->b->name: %s \n", buk->b->name);
        return buk;
    }
    if (buk->next == NULL) {
        return NULL;
    }
    find_in_bucket(buk->next, busstop_name);
}

// tfl.gov.uk/tfl/syndication/feeds/bus-sequences.csv
