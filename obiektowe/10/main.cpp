#include "klasa.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]){
    if(argc!=2){
        cout<<"Usage: "<<endl;
        cout<<"prog.exe var"<<endl;
        cout<<endl;
        cout<<"var - the value of a variable"<<endl;
        return 1;
    }
    else{
        int var = stoi(argv[1]);
        Klasa k = *(new Klasa(var));

        cout<<k.get_x();

        return 0;
    }
}