#pragma once
#include <stdint.h>


struct Node {
  uint8_t value;
  struct Node *next;
};

struct List {
  struct Node *head;
  uint32_t len;
};


struct Node * create_node(uint8_t value);
struct List * create_list();
void list_push(struct List * list, uint8_t value);
uint8_t list_pop(struct List *list);
uint8_t list_get(struct List * list, uint32_t index);
