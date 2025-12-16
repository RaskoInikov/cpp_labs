#include "../headers/SmartClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>
#include "../utils/error_utils.h"
#include <regex>

SmartClock::SmartClock() : ElectronicClock(), osVersion() {}
SmartClock::SmartClock(const String &brand, const String &model, int year, int batteryLife, const String &osVersion)
    : ElectronicClock(brand, model, year, batteryLife), osVersion(osVersion) {}
SmartClock::SmartClock(const SmartClock &other) { *this = other; }

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

void SmartClock::displayHeader() const
{
    ElectronicClock::displayHeader();
    std::cout << std::left
              << std::setw(15) << "OS Version";
}

std::ostream &operator<<(std::ostream &os, const SmartClock &sc)
{
    os << static_cast<const ElectronicClock &>(sc);
    os << std::left
       << std::setw(15) << sc.getOsVersion();
    return os;
}

std::istream &operator>>(std::istream &is, SmartClock &sc)
{
    is >> static_cast<ElectronicClock &>(sc);

    std::string s = checkAlphaNumericSingleWord(
        is, "Enter OS version: ");
    sc.osVersion = String(s.c_str());

    return is;
}

void SmartClock::edit()
{
    ElectronicClock::edit();
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- SmartClock Edit ---\n1. Change OS Version\n0. Done" << std::endl;
        handleUserInput(choice);

        String s;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new OS version: ";
            std::cin >> s;
            setOsVersion(s);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}
