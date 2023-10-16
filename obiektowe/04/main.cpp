#include "tkonto.h"

int main(int argv, char* argc[]){
    TKonto konto1;
    TKonto konto2(
        "Bartosz Geodecki",
        "75649823756498237564982375649837",
        500.43
    );
    konto1.setNumer("12381238123812381238123812381238");
    konto1.setNumer("01940150"); // nie uda sie
    konto1.setNumer("7240859275025257230750275023570257203"); // nie uda sie
    konto1.nazwa = "Karol W.";
    konto1.wplata(100);
    cout<<konto1.toString();

    konto2.wplata(12.1);
    konto2.wyplata(0.52);
    cout<<konto2.toString();

    cout << "===== Wykonuje przelew na 100 zl ====="<<endl;
    konto2.przelew(&konto1, 100);

    cout<<konto1.toString();
    cout<<konto2.toString();

    return 0;
}