#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char const *argv[], char const *envp[])
{
  struct List *list = create_list();

  list_push(list, 'a');
  list_push(list, 'b');
  list_push(list, 'c');

  uint8_t x = list_get(list, 0);
  printf("%c\n", x);

  list_push(list, 'd');


  uint8_t y = list_get(list, 3);

  printf("%c\n", y);
  printf("%u\n", list->len);

  uint8_t last;
  printf("Taking down elements\n");

  while(list->len){
    last = list_pop(list);
    printf("%c\n", last);
  }

  free(list);
  return 0;
}
