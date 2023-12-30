
struct Node {
  char value;
  struct Node *next;
};

struct List {
  struct Node *head;
  unsigned int len;
};


struct Node * create_node(char value);
struct List * create_list();
void list_push(struct List * list, char value);
char list_pop(struct List *list);
char list_get(struct List * list, unsigned int index);
