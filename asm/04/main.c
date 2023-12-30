#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char const *argv[], char const *envp[])
{
  struct List *list = create_list();

  list_push(list, 'a');
  list_push(list, 'b');
  list_push(list, 'c');

  char x = list_get(list, 0);
  printf("%c\n", x);

  list_push(list, 'd');


  char y = list_get(list, 3);

  printf("%c\n", y);
  printf("%u\n", list->len);

  char last;
  printf("Taking down elements\n");

  while(list->len){
    last = list_pop(list);
    printf("%c\n", last);
  }

  free(list);
  return 0;
}
