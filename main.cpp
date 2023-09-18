#include <iostream>

using namespace std;

class Samochodzik;

class Samochodzik
{
public:
    Samochodzik(string name, string color, float weight, string number);
    string name;
    string color;

    void load(float weight);
    void unload(float weight);

    float getWeight();

    string getNumber();

private:
    float loadWeight;
    float weight; // domyślna waga to 1t
protected:
    string regNumber;
    // dostępne w klasach pochodych
};
Samochodzik::Samochodzik(string name, string color, float weight, string number)
{
    this->name = name;
    this->color = color;
    this->weight = weight;
    this->regNumber = number;
}

void Samochodzik::load(float weight)
{
    if (weight > 0)
    {
        this->loadWeight += weight;
    }
    else
    {
        throw "Negative weight";
    }
}

void Samochodzik::unload(float weight)
{
    if ((weight > 0) && (this->loadWeight >= weight))
    {
        this->loadWeight -= weight;
    }
    else
    {
        throw "Negative weight";
    }
}

float Samochodzik::getWeight()
{
    return this->weight + this->loadWeight;
}

string Samochodzik::getNumber()
{
    return this->regNumber;
}

int main(int argc, char const *argv[])
{
    cout << "Hello World" << endl;
    Samochodzik *multipla = new Samochodzik("multipla", "czerwony", 1000, "VW-1234-PL-12.01.2020-23428BE42A09C");
    
    multipla->load(12);  // ładujemy 12 kg
    multipla->unload(8); // wyciągamy 8 kg
    multipla->load(24);
    
    cout << "Multipla wazy " << multipla->getWeight() << "kg" << endl; // polskie znaki nie wchodzą;
    cout << "Numer Multipli to: " << multipla->getNumber() << endl;
    return 0;
}