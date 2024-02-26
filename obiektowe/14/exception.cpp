#include "exception.h"

TrojkotWyjotek::TrojkotWyjotek(int a, int b, int c):bokA(a),bokB(b),bokC(c){}

std::string TrojkotWyjotek::to_string()
{
    std::stringstream ss;
    ss<<"Trojkot o bokach ("<<bokA<<", "<<bokB<<", "<<bokC<<") nie istnieje"<<std::endl;
    return std::string(ss.str());
}
