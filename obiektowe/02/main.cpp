#include "ryba.cpp"

Ryba wczytajDaneRyby(){
    string gatunek;
    int rozmiar;
    float waga;
    cout<<endl;
    cout<<"Podaj gatunek ryby: ";
    cin>>gatunek;
    cout<<"Podaj rozmiar ochronny: ";
    cin>>rozmiar;
    cout<<"Podaj wage ryby: ";
    cin>>waga;

    Ryba *ryba = new Ryba(gatunek, rozmiar, waga);
    return *ryba ;
}

int main(int argc, char const *argv[]){
    Ryba ryby[3];
    for(int i=0; i<3; i++){
        ryby[i] = wczytajDaneRyby();
    }
    ;;;;;;;;;;;;;;;;;;;;;

    return 0;
}