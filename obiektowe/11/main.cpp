#include <iostream>
#include "prostokat.h"
#include "trojkat.h"
#include "figura.h"

#define TABLE_LEN 10

using namespace std;

/* single responsibility principle */
void znajdz_w_tabeli_figure_o_najwiekszej_powierzchni_i_wypisz_informacje_o_niej_na_ekranie(Figura** tab, int len){
    int max_ind = 0;
    float max_pole = 0;
    for (int i = 0; i < len; i++)
    {
        if(!tab[i]) continue;
        Figura* f = tab[i];
        if(f->pole>max_pole){
            max_pole = f->pole;
            max_ind = i;
        }
    }
    cout<<"Najwieksza figura to "+tab[max_ind]->info()<<endl;
    
}

int main(){
    Figura* tab[TABLE_LEN] = {0};
    Figura *fig = new TrojkatRownoboczny(12, "trojkat ABC");
    tab[0] = fig;
    fig = new Prostokat(12, 12, "dziwny kwadrat");
    tab[1] = fig;
    fig = Prostokat::kwadrat(15, "inny kwadrat");
    tab[2] = fig;
    fig = new TrojkatRownoboczny(240, "duzy trojkat");
    tab[3] = fig;
    fig = new Prostokat(22, 22, "kwadrat Q");
    tab[4] = fig;
    for (auto *f : tab)
    {
        if(!f) continue;
        f->obliczObwod();
        f->obliczPole();
        cout<<f->info()<<endl;
    }

    znajdz_w_tabeli_figure_o_najwiekszej_powierzchni_i_wypisz_informacje_o_niej_na_ekranie(tab, TABLE_LEN);
    
}