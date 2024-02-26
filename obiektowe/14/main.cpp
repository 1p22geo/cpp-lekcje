#include "main.h"

int main(int argc, char const *argv[]){
    int a,b,c;
    std::cout<<"Podaj boki trojkota jako liczby calkowite"<<std::endl;
    std::cin>>a>>b>>c;
    
    float p = (a+b+c)/2.0;
    std::cout<<p;
    float S = sqrt(p * (p-a) * (p-b) * (p-c));

    std::cout<<std::endl<<"Pole trojkota to "<<S<<std::endl;

    return 0;
}