#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bus_network.h"


int read_file(int num_lines, char * filename, char *(*text[]), int capital)
{
    FILE* fp;
    int MAX_LEN = 256;
    fp = fopen(filename, "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

    char buffer[MAX_LEN];
    int i = 0;
    while (fgets(buffer, MAX_LEN, fp))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        text[i] = malloc(MAX_LEN);
        strcpy(text[i], buffer);
        i++;
    }
    fclose(fp);
    return 0;
}


int main()
{

    int num_1 = 100;
    char * bus1[num_1];

    read_file(num_1, "data_processing/bus_times/1.txt", &bus1, 0);

    for (int i=0; i < num_1; i ++) {
        printf("\n%s", bus1[i]);
    }


    // int len_routes = 100;
    // char *busstop_names_routes[len_routes];
    // read_file(len_routes, "bus_sequences/stop_name.txt", &busstop_names_routes, 1);
    // char name[50];

    // for ( int i=0 ; i < 10 ; i ++ ) {
    //     memcpy(name, &(bus1[i][10]), sizeof(bus1[i]) - 9 * sizeof(*(bus1[i])) );
    //     printf("\n%s", name);
    // }
}