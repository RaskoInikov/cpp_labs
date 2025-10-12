#include "../headers/SmartClock.h"
#include <iostream>

SmartClock::SmartClock() : ElectronicClock(), osVersion() {}

SmartClock::SmartClock(const String &brand, const String &model, int year, int batteryLife, const String &osVersion)
    : ElectronicClock(brand, model, year, batteryLife), osVersion(osVersion) {}

SmartClock::SmartClock(const SmartClock &other)
{
    *this = other;
}

SmartClock::~SmartClock() {}

SmartClock &SmartClock::operator=(const SmartClock &other)
{
    if (this == &other)
        return *this;
    ElectronicClock::operator=(other);
    osVersion = other.osVersion;
    return *this;
}

String SmartClock::getOsVersion() const { return osVersion; }
void SmartClock::setOsVersion(const String &v) { osVersion = v; }

void SmartClock::serialize(std::ostream &os) const
{
    ElectronicClock::serialize(os);
    os << "OS Version: " << osVersion << '\n';
}

void SmartClock::deserialize(std::istream &is)
{
    ElectronicClock::deserialize(is);
    String tmp;
    std::cout << "Enter OS version (single line): ";
    is >> tmp;
    osVersion = tmp;
}

std::ostream &operator<<(std::ostream &os, const SmartClock &sc)
{
    sc.serialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, SmartClock &sc)
{
    sc.deserialize(is);
    return is;
}
