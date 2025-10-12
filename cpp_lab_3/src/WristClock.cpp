#include "../headers/WristClock.h"
#include "../utils/string_utils.h"
#include <iostream>

WristClock::WristClock() : MechanicalClock(), strapLength(0) {}
WristClock::WristClock(const String &brand, const String &model, int year, int windingInterval, int strapLength)
    : MechanicalClock(brand, model, year, windingInterval), strapLength(strapLength) {}
WristClock::WristClock(const WristClock &other) { *this = other; }
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

std::ostream &operator<<(std::ostream &os, const WristClock &wc)
{
    os << static_cast<const MechanicalClock &>(wc);
    os << "Strap length (mm): " << wc.strapLength << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, WristClock &wc)
{
    is >> static_cast<MechanicalClock &>(wc);
    String tmp;
    std::cout << "Enter strap length (mm): ";
    is >> tmp;
    wc.strapLength = stringToInt(tmp);
    return is;
}
