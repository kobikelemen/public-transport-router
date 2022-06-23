
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


        // if (capital == 1) {

          // int it = strlen(text[i]);
          // for (int j=0; j < it; j++) {
          //   char c = text[i][j];
          //   text[i][j] = toupper(c);
          // }

          // char *c = malloc(sizeof(text[i]));
          // printf("strlen(text[i]): %i\n",strlen(text[i]));
          // char c[strlen(text[i])];
          // for (int j=0; j < strlen(text[i]); j++) {
          //   c[i] = toupper((unsigned char ) text[i][j]);  
          // }
          // printf("c: %s\n", c);
          // strcpy(text[i], c);
          // text[i] = c;

        //   for (int j = 0; text[i][j]!='\0'; j++) {
        //     if(text[i][j] >= 'a' && text[i][j] <= 'z') {
        //         printf("YO\n");
        //         text[i][j] = text[i][j] -32;
        //     }
        //   }
        // }
        // printf(" capital: %i\n", capital);
        // printf(" text[i] %s\n", text[i]);
        
        i++;
    }
    fclose(fp);
    return 0;
}



