#include "../headers/ElectronicClock.h"
#include <iostream>

static int ec_stringToInt(const String &s)
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

ElectronicClock::ElectronicClock() : Clock(), batteryLife(0) {}

ElectronicClock::ElectronicClock(const String &brand, const String &model, int year, int batteryLife)
    : Clock(brand, model, year), batteryLife(batteryLife) {}

ElectronicClock::ElectronicClock(const ElectronicClock &other)
{
    *this = other;
}

ElectronicClock::~ElectronicClock() {}

ElectronicClock &ElectronicClock::operator=(const ElectronicClock &other)
{
    if (this == &other)
        return *this;
    Clock::operator=(other);
    batteryLife = other.batteryLife;
    return *this;
}

int ElectronicClock::getBatteryLife() const { return batteryLife; }
void ElectronicClock::setBatteryLife(int hours) { batteryLife = hours; }

void ElectronicClock::serialize(std::ostream &os) const
{
    Clock::serialize(os);
    os << "Battery life (hours): " << batteryLife << '\n';
}

void ElectronicClock::deserialize(std::istream &is)
{
    Clock::deserialize(is);
    String tmp;
    std::cout << "Enter battery life (hours): ";
    is >> tmp;
    batteryLife = ec_stringToInt(tmp);
}

std::ostream &operator<<(std::ostream &os, const ElectronicClock &ec)
{
    ec.serialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, ElectronicClock &ec)
{
    ec.deserialize(is);
    return is;
}
