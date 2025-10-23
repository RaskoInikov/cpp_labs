#include "../headers/WristClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

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

void WristClock::displayHeader() const { Clock::displayHeader(); }

std::ostream &operator<<(std::ostream &os, const WristClock &wc)
{
    os << std::left
       << std::setw(15) << wc.getBrand()
       << std::setw(15) << wc.getModel()
       << std::setw(8) << wc.getYear()
       << std::setw(15) << "-"
       << std::setw(18) << wc.getWindingInterval()
       << std::setw(15) << "-"
       << std::setw(12) << "-"
       << std::setw(15) << wc.getStrapLength();
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