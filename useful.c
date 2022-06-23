
#include "useful.h"



void capitalise(char ** s)
{
  char c[strlen(*s)];
    for (int i=0; i < strlen(*s); i++) {
        c[i] = toupper((unsigned char ) (*s)[i]);
    }
    *s = c;
}

void capitalise_text(int num_lines, char *(*text[]))
{
  for (int i=0; i < num_lines; i++ ){
    capitalise(&((*text)[i]));
  }
}



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



