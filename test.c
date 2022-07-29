#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bus_network.h"
#include <time.h>


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


    // char a[10] = "abcd";
    // char b[] = "efgh";
    // strcat(a,b);
    // printf("%s ", a);

    // int r1 = rand();
    // int r2 = rand();

    // srand( time(NULL) );
    for (int i=0; i < 20; i++) {
      printf("\nrand: %i ", rand()%2+1);  
    }
    
    printf("\nrand: %i ", rand()%2+1);




    // int num_1 = 120;
    // char * bus1[num_1];

    // char bus_routes[num_1][1];
    // char arrival_mins[num_1][2];
    // char bsnames[num_1][100];

    // read_file(num_1, "data_processing/bus_times/1.txt", &bus1, 0);


    // int b1 = 1;
    // int b2 = 9;
    // int endlen;

    // for (int i=0; i < num_1; i ++) {
    //     // printf("\n%s", bus1[i]);

    //     memcpy(bus_routes[i], &(bus1[i][0]), sizeof(*(bus1[i])));
    //     memcpy(arrival_mins[i], &(bus1[i][4]), 2 * sizeof(*(bus1[i])) );


    //     // char *p = & (*bus1[i]);
    //     // for (int j=0; j < 10; j ++) {
    //     //     p++; // now points to start of name part
    //     // }

    //     // endlen = 0;

    //     // while (strcmp(*p, "\0") != 0) {
    //     //     p++;
    //     //     endlen++;
    //     // }



    //     memcpy(bsnames[i], &(bus1[i][10]), (strlen(bus1[i]) - 10) * sizeof(*(bus1[i])));

    //     printf("\nroute: %s", bus_routes[i]);
    //     printf("\nmins: %i", atoi(arrival_mins[i]));
    //     // char * t = bsnames[i];
    //     printf("\nname:%s", bsnames[i]);

        
    // }
}