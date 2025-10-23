#include "../headers/WallClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

WallClock::WallClock() : MechanicalClock(), diameter(0) {}
WallClock::WallClock(const String &brand, const String &model, int year, int windingInterval, int diameter)
    : MechanicalClock(brand, model, year, windingInterval), diameter(diameter) {}
WallClock::WallClock(const WallClock &other) { *this = other; }
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

void WallClock::displayHeader() const { Clock::displayHeader(); }

std::ostream &operator<<(std::ostream &os, const WallClock &wc)
{
    os << std::left
       << std::setw(15) << wc.getBrand()
       << std::setw(15) << wc.getModel()
       << std::setw(8) << wc.getYear()
       << std::setw(15) << "-"
       << std::setw(18) << wc.getWindingInterval()
       << std::setw(15) << "-"
       << std::setw(12) << wc.getDiameter()
       << std::setw(15) << "-";
    return os;
}

std::istream &operator>>(std::istream &is, WallClock &wc)
{
    is >> static_cast<MechanicalClock &>(wc);
    String tmp;
    std::cout << "Enter diameter (mm): ";
    is >> tmp;
    wc.diameter = stringToInt(tmp);
    return is;
}