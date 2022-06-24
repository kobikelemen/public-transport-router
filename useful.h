#ifndef USEFUL
#define USEFUL


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct list
{
    char * s;
    struct list * next;
}list;

list * append_list(list *lis, char * str);
void print_list(list * l );
int read_file(int num_lines, char * filename, char *(*text[]), int capital);
void capitalise(char ** s);
void capitalise_text(int num_lines, char *(*text[]));
#endif