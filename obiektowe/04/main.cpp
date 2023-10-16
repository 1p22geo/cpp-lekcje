#include "tkonto.h"

int main(int argv, char* argc[]){
    TKonto konto1;
    TKonto konto2(
        "Bartosz Geodecki",
        "7564982375649823756498237564983",
        500.43
    );
    konto1.setNumer("1238123812381238123812381238123");
    konto1.nazwa = "Karol W.";
    konto1.wplata(100);
    cout<<konto1.toString();

    konto2.wplata(12.1);
    konto2.wyplata(0.52);
    cout<<konto2.toString();
    return 0;
}