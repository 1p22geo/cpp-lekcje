#include "main.h"

int main(int argc, char const *argv[]){
    int a,b,c;
    std::cout<<"Podaj boki trojkota jako liczby calkowite"<<std::endl;
    std::cin>>a>>b>>c;
    
    if( (a+b<=c)||(a+c<=b)||(c+b<=a) ){
        std::cout<<"e byku ale to nie ma trojkot"<<std::endl;
        return 1;
    }

    float p = (a+b+c)/2.0;
    float S = sqrt(p * (p-a) * (p-b) * (p-c));

    std::cout<<std::endl<<"Pole trojkota to "<<S<<std::endl;

    return 0;
}