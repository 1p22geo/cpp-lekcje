#include "main.h"

int main(int argc, char const *argv[]){
    polaRownania dane = pobierzDane();
    Rownanie r(dane);
    std::cout<<r.to_string()<<std::endl;
    wynik w;
    try{
        w = r.policz();
        if(w.x1 == w.x2){
            std::cout<<"Jest jedno rozwiazanie: "<<w.x1<<std::endl;
        }
        else{
            std::cout<<"Sa dwa rozwiazania: "<<w.x1<<" oraz "<<w.x2<<std::endl;
        }
    }
    catch(Error *er){
        std::cout<<"Wystapil blad: "<<er->_er->to_string()<<std::endl;
    }
    return 0;
}