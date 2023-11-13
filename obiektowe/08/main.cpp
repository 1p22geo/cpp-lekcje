#include "pies.h"
#include "kot.h"

#include <iostream>
#include <time.h>
#include <string.h>

using namespace std;

void ktoStarszy(Kot a, Pies b){
    time_t czas = time(0);
    tm *struktCzas = localtime(&czas);
    int rok = struktCzas->tm_year + 1900;
    int piesLata = rok -  b.rok_ur;
    int kotLata = a.lata;

    if(piesLata > kotLata){
        cout << "Pies jest starszy "<<endl;
    }
    else if(kotLata > piesLata){
        cout << "Kot jest starszy "<<endl;
    }
    else{
        cout <<"Mają tyle samo lat"<<endl;
    }
    
}

int main(){
    Kot kotek(5, "Bob");
    Pies piesek = *new Pies(1901, "paweu");
    kotek.przedstawSie();
    piesek.przedstawSie();

    ktoStarszy(kotek, piesek);
    return 0;
}