#include <iostream>
#include "czas.h"

std::ostream &operator<<(std::ostream &stream, Czas &that)
{
    return stream<<that.ToString();
}



int main(int argc, char const *argv[]){
    Czas c(533);
    std::cout<<c<<std::endl;
    Czas czas2(5, 34);
    Czas czas3 = c + czas2;
    std::cout<<czas3<<std::endl;
    std::cout<<czas3.ToString()<<std::endl;
    Czas czas4 = c - czas2;
    if(czas4>czas3){
        std::cout<<czas4<<" jest wiekszy"<<std::endl;
    }
    else{
        std::cout<<czas4<<" nie jest wiekszy"<<std::endl;
    }
    
    return 0;
}