#include "../headers/SmartClock.h"
#include "../utils/string_utils.h"
#include <iostream>

SmartClock::SmartClock() : ElectronicClock(), osVersion() {}
SmartClock::SmartClock(const String &brand, const String &model, int year, int batteryLife, const String &osVersion)
    : ElectronicClock(brand, model, year, batteryLife), osVersion(osVersion) {}
SmartClock::SmartClock(const SmartClock &other) { *this = other; }
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

std::ostream &operator<<(std::ostream &os, const SmartClock &sc)
{
    os << static_cast<const ElectronicClock &>(sc);
    os << "OS Version: " << sc.osVersion << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, SmartClock &sc)
{
    is >> static_cast<ElectronicClock &>(sc);
    String tmp;
    std::cout << "Enter OS version (single line): ";
    is >> tmp;
    sc.osVersion = tmp;
    return is;
}
