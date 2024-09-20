#include "main.hpp"
#include "lib_list/lib_list.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Hello world!" << std::endl;
  DoubleList::List *list = DoubleList::create_list();
  DoubleList::append(list, 0x00);
  DoubleList::append(list, 0xde);
  DoubleList::append(list, 0xad);
  DoubleList::append(list, 0xbe);
  DoubleList::append(list, 0xef);
  DoubleList::remove(list, 0);
  DoubleList::print_list(list);

  std::cout << std::hex << (0xFF & DoubleList::retrieve(list, 2));
  DoubleList::destroy_list(list);
  return 0;
}
