
#include "useful.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int read_file(int num_lines, char * filename)
{
    FILE* fp;
    int MAX_LEN = 256;
    char *text[num_lines];

    

    fp = fopen(filename, "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

    char buffer[MAX_LEN];
    int i = 0;
    printf("YO");
    while (fgets(buffer, MAX_LEN, fp))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        // printf("%s ", buffer);
        // char *t = buffer;
        text[i] = malloc(MAX_LEN);
        strcpy(text[i], buffer);
        i++;
    }
    fclose(fp);
    for (int j=0; j < num_lines; j++) {
        printf("%s ",text[j]);
    }
    return 0;
}


int main()
{
    read_file(18951, "bus_data/names.txt");
}