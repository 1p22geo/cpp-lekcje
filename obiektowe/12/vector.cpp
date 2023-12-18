#include "vector.h"

Vector::Vector()
{
    this->x = 0;
    this->y = 0;
}

Vector::Vector(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Vector::getX()
{
    return this->x;
}

float Vector::getY()
{
    return this->y;
}

std::string Vector::to_string()
{
    return "["+std::to_string(this->x)+", "+std::to_string(this->y)+"]";
}

Vector Vector::operator+(Vector that)
{
    return Vector(this->x + that.x, this->y+ that.y);
}

Vector Vector::operator-(Vector that)
{
    return Vector(this->x - that.x, this->y- that.y);
}
