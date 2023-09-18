#include <iostream>

using namespace std;

class Samochodzik;

class Samochodzik{
    public:
        string name;
        string color;
        void load(float weight){
            if(weight>0){
                this->loadWeight += weight;
            }
            else{
                throw "Negative weight";
            }
        }
        void unload(float weight){
            if((weight>0)&&(this->loadWeight>=weight)){
                this->loadWeight-=weight;
            }
            else{
                throw "Negative weight";
            }
        }
        float getWeight(){
            return this->weight+this->loadWeight;
        }
        string getNumber(){
            return this->regNumber;
        }
    private:
        float loadWeight = 0;
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
    multipla.load(12); //ładujemy 12 kg
    multipla.unload(8); //wyciągamy 8 kg
    multipla.load(24);
    cout <<"Multipla wazy "<< multipla.getWeight()<<"kg"<<endl; // polskie znaki nie wchodzą;
    cout<<"Numer Multipli to: "<<multipla.getNumber()<<endl;
    return 0;
}