#pragma once
#include <string>


class Czas{
    private:
        unsigned long minuty;
    public:
        Czas(unsigned long minuty);
        Czas(unsigned long godziny, unsigned long minuty);
        std::string ToString();
        Czas operator+(Czas &that);
        Czas operator-(Czas &that);
        bool operator>(Czas &that);
        friend std::ostream &operator<<(std::ostream &stream, Czas &that);
};