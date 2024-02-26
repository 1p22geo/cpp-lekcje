#include "main.h"

int main(int argc, char const *argv[]){
    int a,b,c;
    std::cout<<"Podaj boki trojkota jako liczby calkowite"<<std::endl;
    std::cin>>a>>b>>c;
    float S;
    try{
        S = pole_trojkota(a,b,c);
    }
    catch(TrojkotWyjotek w){
        std::cerr<<w.to_string();
        return 1;
    }

    std::cout<<"Pole trojkota to "<<S<<std::endl;

    return 0;
}