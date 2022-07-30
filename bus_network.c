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




int find_in_bucket(bucket ** buk, char * busstop_name, int add_busroute)
{

    if (strcmp((*buk)->b->name, busstop_name) == 0) {
        append_buses((&(*buk)->b), add_busroute);
        return (*buk)->b->id;
    }

    if ((*buk)->next == NULL) {
        return -1;
    }
    
    find_in_bucket(&((*buk)->next), busstop_name, add_busroute);
}


int add_neighbour(
    neighbour *bgraph[], bucket ** b, bucket ** bnext, char * busnum, 
    int dt, char * bsname, char * bsnamenext, int seq_locn, int seq_loce, 
    int seq_locn_next, int seq_loce_next
    )
{
    if ((*bnext) == NULL) {
        return -2;
    } else if ((*b) == NULL) {
        return -1;
    }
    
    // if (strcmp(bsname, "CANADA WATER BUS STATION") == 0) {
    //     printf("\n\n LOOKING FOR COORDS: \n\n");
    // }

    while ( (strcmp((*bnext)->b->name, bsnamenext) != 0) || (seq_loce_next != (*bnext)->b->easting) || (seq_locn_next != (*bnext)->b->northing)) {
        // printf("\n bsname: %s, name: %s, seq_loce_next: %i, easting: %i, seq_locn_next: %i, northing: %i ", bsname, (*bnext)->b->name, seq_loce_next, (*bnext)->b->easting, seq_locn_next, (*bnext)->b->northing);
        *bnext = (*bnext)->next;
        if (*bnext == NULL) {
            // printf("BNEXT NOT FOUND -- %s!\n", bsnamenext);
            return -2;
        }
    }


    // printf("\n");
    if (strcmp(bsname, "WATERLOO ROAD") == 0) {
            printf("\nBUCKET: ");
            printf(" %s current e: %i n: %i     target e: %i n: %i\n", (*b)->b->name, (*b)->b->easting, (*b)->b->northing, seq_loce, seq_locn);
        }
    while ( (strcmp((*b)->b->name, bsname) != 0) || (seq_loce != (*b)->b->easting) || (seq_locn != (*b)->b->northing)) {
        
        
        *b = (*b)->next;
        if (*b == NULL) {
            // printf("B NOT FOUND -- %s!\n", bsname);
            return -1;
        }
        if (strcmp(bsname, "WATERLOO ROAD") == 0) {
            printf("\nINSIDE");
            printf("\nBUCKET: ");
            printf(" %s e: %i n: %i", (*b)->b->name, (*b)->b->easting, (*b)->b->northing);
        }
    }
    
    
    if (bgraph[(*b)->b->id] == NULL) {
        bgraph[(*b)->b->id] = malloc(sizeof(neighbour));
        strcpy(bgraph[(*b)->b->id]->bus_number, busnum);
        (bgraph[(*b)->b->id])->time = dt;
        (bgraph[(*b)->b->id])->next = NULL;
        (bgraph[(*b)->b->id])->node = (*bnext)->b;
        return (*b)->b->id;
    } else {
        neighbour * n = bgraph[(*b)->b->id];
        while(n->next != NULL) {
            n = n->next;
        }
        n->next = malloc(sizeof(neighbour));
        strcpy(n->next->bus_number, busnum);
        n->next->time = dt;
        n->next->next = NULL;
        n->next->node = (*bnext)->b;
        if (strcmp(bsname, "WATERLOO ROAD") == 0 || strcmp(bsnamenext, "WATERLOO ROAD") == 0) {
            printf("\n\nFOUND %s e: %i  n: %i --> %s e: %i n: %i", bsname,(*b)->b->easting, (*b)->b->northing, bsnamenext, n->next->node->easting, n->next->node->northing );
            printf("\n BUT TARGET e: %i n: %i next e: %i next n: %i", seq_loce, seq_locn, seq_loce_next, seq_locn_next);
        }
        return (*b)->b->id;
    } 
     
    
}




// tfl.gov.uk/tfl/syndication/feeds/bus-sequences.csv
