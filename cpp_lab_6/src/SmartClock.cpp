#include "../headers/SmartClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>
#include "../utils/error_utils.h"
#include <regex>
#include <cstring>

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

void SmartClock::writeText(std::ostream &os) const
{
    ElectronicClock::writeText(os);
    os << std::setw(15) << osVersion;
}

void SmartClock::readText(std::istream &is)
{
    ElectronicClock::readText(is);
    std::string s;
    is >> s;
    osVersion = String(s.c_str());
}

void SmartClock::writeBinary(std::ostream &os) const
{
    ElectronicClock::writeBinary(os);

    size_t len = std::strlen(osVersion.c_str());
    char buf[sizeof(size_t)];
    std::memcpy(buf, &len, sizeof(len));
    os.write(buf, sizeof(len));
    os.write(osVersion.c_str(), len);
}

bool SmartClock::readBinary(std::istream &is)
{
    if (!ElectronicClock::readBinary(is))
        return false;

    size_t len;
    char buf[256];

    if (!is.read(buf, sizeof(size_t)))
        return false;
    std::memcpy(&len, buf, sizeof(size_t));
    if (len >= sizeof(buf))
        return false;
    if (!is.read(buf, len))
        return false;

    buf[len] = '\0';
    osVersion = String(buf);

    return true;
}
