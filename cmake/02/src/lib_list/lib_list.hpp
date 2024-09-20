namespace DoubleList {
struct List {
  struct Node *first;
  struct Node *last;
  unsigned int length;
};

struct Node {
  Node *next;
  Node *prev;
  unsigned char value;
};

List *create_list();
void destroy_list(List *list);
void print_list(List *list);
void append(List *list, char elem);
unsigned char retrieve(List *list, unsigned int index);
void remove(List *list, unsigned int index);
} // namespace DoubleList
