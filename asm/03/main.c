#include <stdio.h>
#include <stdlib.h>

#include "stuff.h"

void stuff();
int main();

int main(int argc, char const *argv[], char const *envp[]){
  stuff();
  return 0;
}

void stuff(){
  char *hello = malloc(sizeof(char[10]));
  *hello = 'h';
  spaces(hello+1, 3);
  *(hello+4) = 'e';
  *(hello+5) = 'l';
  *(hello+6) = 'l';
  *(hello+7) = 'o';
  *(hello+8) = '\n';
  *(hello+9) = (char)0;


  printf(hello);
  free(hello);
}
