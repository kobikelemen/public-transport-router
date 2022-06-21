#include "bus_network.h"



void append_buses(buses *bus_head, int bus)
{
    buses *b = malloc(sizeof(buses));
    b->bus = bus;
    bus_head->next = b;

}


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
    printf("\t%s", buck->b.name);
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

// tfl.gov.uk/tfl/syndication/feeds/bus-sequences.csv
