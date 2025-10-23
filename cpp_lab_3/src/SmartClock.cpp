#include "../headers/SmartClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

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

void SmartClock::displayHeader() const { Clock::displayHeader(); }

std::ostream &operator<<(std::ostream &os, const SmartClock &sc)
{
    os << std::left
       << std::setw(15) << sc.getBrand()
       << std::setw(15) << sc.getModel()
       << std::setw(8) << sc.getYear()
       << std::setw(15) << sc.getBatteryLife()
       << std::setw(18) << "-"
       << std::setw(15) << sc.getOsVersion()
       << std::setw(12) << "-"
       << std::setw(15) << "-";
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