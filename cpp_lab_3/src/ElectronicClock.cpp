#include "../headers/ElectronicClock.h"
#include "../utils/string_utils.h"
#include <iostream>

ElectronicClock::ElectronicClock() : Clock(), batteryLife(0) {}
ElectronicClock::ElectronicClock(const String &brand, const String &model, int year, int batteryLife)
    : Clock(brand, model, year), batteryLife(batteryLife) {}
ElectronicClock::ElectronicClock(const ElectronicClock &other) { *this = other; }
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

std::ostream &operator<<(std::ostream &os, const ElectronicClock &ec)
{
    os << static_cast<const Clock &>(ec);
    os << "Battery life (hours): " << ec.batteryLife << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, ElectronicClock &ec)
{
    is >> static_cast<Clock &>(ec);
    String tmp;
    std::cout << "Enter battery life (hours): ";
    is >> tmp;
    ec.batteryLife = stringToInt(tmp);
    return is;
}
