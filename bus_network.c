#include "bus_network.h"



void append_buses(bus_stop **busstop, int bus)
{
    int i=0; 
    while (((*busstop)->bus_list)[i] != 0) {
        i++;
        if ( i > 1000 ) {
            break;
        }
    }
    ((*busstop)->bus_list)[i] = bus;
}

void print_buses_at_busstop(int bu[], int arrsize)
{
    
    for (int j=0; j < arrsize; j++) {
        printf("\t%s", bu[j]);
    }
}


void print_busstops(bucket * hashtable[], int DICT_SIZE)
{
    for (int i=0; i < DICT_SIZE; i++) {
        printf("\n\n name: %s \n", hashtable[i]->b->name);
        printf("buses:   ");
        print_buses_at_busstop(hashtable[i]->b->bus_list, 20);
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
    if (buck->b == NULL) {
        printf("\nOHHH\n");
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



// bucket * find_forreal(bucket ** buk, char * busstop_name)
// {

//     if (strcmp((*buk)->b->name, busstop_name) == 0) {
        
//         // append_buses((&(*buk)->b));
//         return *buk;
//     }

//     if ((*buk)->next == NULL) {
//         return 2;
//     }
//     find_forreal(&((*buk)->next), busstop_name);
// }


int find_in_bucket(bucket ** buk, char * busstop_name, int add_busroute)
{

    if (strcmp((*buk)->b->name, busstop_name) == 0) {
        append_buses((&(*buk)->b), add_busroute);
        return 0;
    }

    if ((*buk)->next == NULL) {
        return 2;
    }
    
    find_in_bucket(&((*buk)->next), busstop_name, add_busroute);
}


int add_neighbour(neighbour ** n, bucket ** b, bucket ** bnext, char * busnum, int dt, char * bsname, char * bsnamenext)
{
    strcpy((*n)->bus_number, busnum);
    (*n)->time = dt;
    (*n)->next = NULL;


    while ( strcmp((*bnext)->b->name, bsnamenext) != 0) {
        *bnext = (*bnext)->next;
        if (*bnext == NULL) {
            printf("BNEXT NOT FOUND!\n");
            return -1;
        }
    }

    while ( strcmp((*b)->b->name, bsname) != 0) {
        *b = (*b)->next;
        if (*b == NULL) {
            printf("B NOT FOUND!\n");
            return -1;
        }
    }

    (*n)->node = (*bnext)->b;

    return (*b)->b->id;


    


}




// tfl.gov.uk/tfl/syndication/feeds/bus-sequences.csv
