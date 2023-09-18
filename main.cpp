#include <iostream>

using namespace std;

class Samochodzik;

class Samochodzik{
    public:
        string name;
        string color;
        float loadWeight;
        float getWeight(){
            if(this->loadWeight<0){
                throw "Negative loadWeight";
            }
            return this->weight+this->loadWeight;
        }
        string getNumber(){
            return this->regNumber;
        }
    private:
        float weight = 1000; // domyślna waga to 1t
    protected:
        string regNumber = "XXXX";
        //dostępne w klasach pochodych
};


int main(int argc, char const *argv[])
{
    cout << "Hello World" << endl;
    Samochodzik multipla;
    multipla.name = "VW Multipla";
    multipla.color = "czerwony";
    multipla.loadWeight = 12; //ładujemy 12 kg
    cout <<"Multipla wazy "<< multipla.getWeight()<<"kg"<<endl; // polskie znaki nie wchodzą;
    cout<<"Numer Multipli to: "<<multipla.getNumber()<<endl;
    return 0;
}