#include "../headers/WallClock.h"
#include <iostream>

static int wall_stringToInt(const String &s)
{
    int res = 0;
    bool neg = false;
    unsigned int i = 0;
    char c = s[i];
    if (c == '-')
    {
        neg = true;
        i = 1;
    }
    for (;; ++i)
    {
        c = s[i];
        if (c == '\0')
            break;
        if (c >= '0' && c <= '9')
            res = res * 10 + (c - '0');
        else
            break;
    }
    return neg ? -res : res;
}

WallClock::WallClock() : MechanicalClock(), diameter(0) {}

WallClock::WallClock(const String &brand, const String &model, int year, int windingInterval, int diameter)
    : MechanicalClock(brand, model, year, windingInterval), diameter(diameter) {}

WallClock::WallClock(const WallClock &other)
{
    *this = other;
}

WallClock::~WallClock() {}

WallClock &WallClock::operator=(const WallClock &other)
{
    if (this == &other)
        return *this;
    MechanicalClock::operator=(other);
    diameter = other.diameter;
    return *this;
}

int WallClock::getDiameter() const { return diameter; }
void WallClock::setDiameter(int mm) { diameter = mm; }

void WallClock::serialize(std::ostream &os) const
{
    MechanicalClock::serialize(os);
    os << "Diameter (mm): " << diameter << '\n';
}

void WallClock::deserialize(std::istream &is)
{
    MechanicalClock::deserialize(is);
    String tmp;
    std::cout << "Enter diameter (mm): ";
    is >> tmp;
    diameter = wall_stringToInt(tmp);
}

std::ostream &operator<<(std::ostream &os, const WallClock &wc)
{
    wc.serialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, WallClock &wc)
{
    wc.deserialize(is);
    return is;
}
