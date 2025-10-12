#include "../headers/MechanicalClock.h"
#include "../utils/string_utils.h"
#include <iostream>

MechanicalClock::MechanicalClock() : Clock(), windingInterval(0) {}
MechanicalClock::MechanicalClock(const String &brand, const String &model, int year, int windingInterval)
    : Clock(brand, model, year), windingInterval(windingInterval) {}
MechanicalClock::MechanicalClock(const MechanicalClock &other) { *this = other; }
MechanicalClock::~MechanicalClock() {}

MechanicalClock &MechanicalClock::operator=(const MechanicalClock &other)
{
    if (this == &other)
        return *this;
    Clock::operator=(other);
    windingInterval = other.windingInterval;
    return *this;
}

int MechanicalClock::getWindingInterval() const { return windingInterval; }
void MechanicalClock::setWindingInterval(int days) { windingInterval = days; }

std::ostream &operator<<(std::ostream &os, const MechanicalClock &mc)
{
    os << static_cast<const Clock &>(mc);
    os << "Winding interval (days): " << mc.windingInterval << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, MechanicalClock &mc)
{
    is >> static_cast<Clock &>(mc);
    String tmp;
    std::cout << "Enter winding interval (days): ";
    is >> tmp;
    mc.windingInterval = stringToInt(tmp);
    return is;
}
