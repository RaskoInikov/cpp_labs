#include "../headers/MechanicalClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

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

void MechanicalClock::displayHeader() const { Clock::displayHeader(); }

std::ostream &operator<<(std::ostream &os, const MechanicalClock &mc)
{
    os << std::left
       << std::setw(15) << mc.getBrand()
       << std::setw(15) << mc.getModel()
       << std::setw(8) << mc.getYear()
       << std::setw(15) << "-"
       << std::setw(18) << mc.getWindingInterval()
       << std::setw(15) << "-"
       << std::setw(12) << "-"
       << std::setw(15) << "-";
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

void MechanicalClock::edit()
{
    Clock::edit();

    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- MechanicalClock Additional Editing ---" << std::endl;
        std::cout << "1. Change Winding Interval" << std::endl;
        std::cout << "0. Done" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 0)
            break;

        int val;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new winding interval (days): ";
            std::cin >> val;
            setWindingInterval(val);
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}
