#include "../headers/WristClock.h"
#include <iostream>

static int wc_stringToInt(const String &s)
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

WristClock::WristClock() : MechanicalClock(), strapLength(0) {}

WristClock::WristClock(const String &brand, const String &model, int year, int windingInterval, int strapLength)
    : MechanicalClock(brand, model, year, windingInterval), strapLength(strapLength) {}

WristClock::WristClock(const WristClock &other)
{
    *this = other;
}

WristClock::~WristClock() {}

WristClock &WristClock::operator=(const WristClock &other)
{
    if (this == &other)
        return *this;
    MechanicalClock::operator=(other);
    strapLength = other.strapLength;
    return *this;
}

int WristClock::getStrapLength() const { return strapLength; }
void WristClock::setStrapLength(int mm) { strapLength = mm; }

void WristClock::serialize(std::ostream &os) const
{
    MechanicalClock::serialize(os);
    os << "Strap length (mm): " << strapLength << '\n';
}

void WristClock::deserialize(std::istream &is)
{
    MechanicalClock::deserialize(is);
    String tmp;
    std::cout << "Enter strap length (mm): ";
    is >> tmp;
    strapLength = wc_stringToInt(tmp);
}

std::ostream &operator<<(std::ostream &os, const WristClock &wc)
{
    wc.serialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, WristClock &wc)
{
    wc.deserialize(is);
    return is;
}
