#include "../headers/SmartClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

SmartClock::SmartClock() : ElectronicClock(), osVersion() {}
SmartClock::SmartClock(const String &brand, const String &model, int year, int batteryLife, const String &osVersion)
    : Clock(brand, model, year), ElectronicClock(brand, model, year, batteryLife), osVersion(osVersion) {}
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

void SmartClock::edit()
{
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- SmartClock Menu ---" << std::endl;
        std::cout << "1. Change Brand" << std::endl;
        std::cout << "2. Change Model" << std::endl;
        std::cout << "3. Change Year" << std::endl;
        std::cout << "4. Change Battery Life" << std::endl;
        std::cout << "5. Change OS Version" << std::endl;
        std::cout << "0. Exit editing" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;
        clearInputBuffer();

        String s;
        int val;

        switch (choice)
        {
        case 1:
            std::cout << "Enter new brand: ";
            std::cin >> s;
            setBrand(s);
            break;
        case 2:
            std::cout << "Enter new model: ";
            std::cin >> s;
            setModel(s);
            break;
        case 3:
            std::cout << "Enter new year: ";
            std::cin >> val;
            setYear(val);
            break;
        case 4:
            std::cout << "Enter new battery life (hours): ";
            std::cin >> val;
            setBatteryLife(val);
            break;
        case 5:
            std::cout << "Enter new OS version: ";
            std::cin >> s;
            setOsVersion(s);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }

        if (choice >= 1 && choice <= 5)
        {
            std::cout << "\n✅ Updated SmartClock:" << std::endl;
            displayHeader();
            std::cout << *this << std::endl;
        }
    }
}
