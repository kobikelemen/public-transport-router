#include "bus_network.h"



void append_buses(buses *bus_head, int bus)
{
    buses *b = malloc(sizeof(buses));
    b->bus = bus;
    bus_head->next = b;

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
    // printf("YOO");
    // printf("YOO %s\n",(*b)->b->name);

    if (b->next == NULL) {
        b->next = a;
        return;
    }
    append_to_bucket(b->next, a);
}


// int is_in_bucket(bucket * buck,)


bucket * find_in_bucket(bucket * buk, char * busstop_name)
{
    // printf("%s ", buk->b->name);

    if (buk->b->name == busstop_name) {
        return buk;
    }
    find_in_bucket(buk->next, busstop_name);
}

// tfl.gov.uk/tfl/syndication/feeds/bus-sequences.csv
