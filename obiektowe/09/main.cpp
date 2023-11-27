#include "pojazd.h"
#include "koparka.h"
#include "taxi.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    Pojazd *pojazd;
    pojazd = new Pojazd("traktor", 1990);
    
    Pojazd *tx;
    tx= new Taxi(12, "czerwona kaksufka", 2001);
    Pojazd *kp;
    kp= new Koparka(24.1, "kopara", 2011);

    Pojazd **parking = new Pojazd*[12];

    parking[0] = new Taxi(4, "taksufka", 2022);
    parking[1] = new Koparka(15.2, "agdasgdgas", 2000);

    cout<<parking[0]->info()<<endl;
    cout<<parking[1]->info()<<endl;

    return 0;
}