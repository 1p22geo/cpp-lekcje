#include "lib_list.hpp"
#include <cstddef>
#include <ios>
#include <iostream>

using namespace DoubleList;

List *DoubleList::create_list() {
  List *list = new List;
  list->first = NULL;
  list->last = NULL;
  list->length = 0;

  return list;
}

void DoubleList::append(List *list, char elem) {
  Node *node = new Node;
  node->value = elem;
  if (list->length == 0) {
    list->first = node;
    list->last = node;
    node->next = NULL;
    node->prev = NULL;
  } else if (list->length >= 1) {
    list->last->next = node;
    node->prev = list->last;
    node->next = NULL;
    list->last = node;
  }
  list->length++;
}

void DoubleList::print_list(List *list) {
  Node *node = list->first;
  while (node != NULL) {
    std::cout << std::hex << (0xFF & node->value);
    std::cout << ' ';
    node = node->next;
  }
  std::cout << std::endl;
}

unsigned char DoubleList::retrieve(List *list, unsigned int index) {
  unsigned int counter = 0;
  Node *node = list->first;
  while (counter < index) {
    node = node->next;
    counter++;
  }
  return node->value;
}

void DoubleList::remove(List *list, unsigned int index) {
  unsigned int counter = 0;
  Node *node = list->first;
  while (counter < index) {
    node = node->next;
    counter++;
  }
  Node *prev = node->prev;
  Node *next = node->next;
  if (prev != NULL)
    prev->next = next;
  else
    list->first = next;
  if (next != NULL)
    next->prev = prev;
  else
    list->last = prev;
  delete node;
  list->length--;
}

void DoubleList::destroy_list(List *list) {
  Node *node = list->first;
  Node *prev = NULL;
  while (node != NULL) {
    prev = node->prev;
    delete node;
    node = prev;
  }
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
}
