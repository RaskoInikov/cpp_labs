#include "../headers/MechanicalClock.h"
#include <iostream>

// helper reuse
static int mc_stringToInt(const String &s)
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

MechanicalClock::MechanicalClock() : Clock(), windingInterval(0) {}

MechanicalClock::MechanicalClock(const String &brand, const String &model, int year, int windingInterval)
    : Clock(brand, model, year), windingInterval(windingInterval) {}

MechanicalClock::MechanicalClock(const MechanicalClock &other)
{
    *this = other;
}

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

void MechanicalClock::serialize(std::ostream &os) const
{
    Clock::serialize(os);
    os << "Winding interval (days): " << windingInterval << '\n';
}

void MechanicalClock::deserialize(std::istream &is)
{
    // reuse base deserialization for brand/model/year
    Clock::deserialize(is);

    String tmp;
    std::cout << "Enter winding interval (days): ";
    is >> tmp;
    windingInterval = mc_stringToInt(tmp);
}

std::ostream &operator<<(std::ostream &os, const MechanicalClock &mc)
{
    mc.serialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, MechanicalClock &mc)
{
    mc.deserialize(is);
    return is;
}
