#include "lib.h"

polaRownania pobierzDane()
{
    polaRownania dane;

    std::cout<<"Wpisz parametry rownania"<<std::endl;
    std::cout<<"a = ";
    std::cin>>dane.a;
    std::cout<<"b = ";
    std::cin>>dane.b;
    std::cout<<"c = ";
    std::cin>>dane.c;

    return dane;
}