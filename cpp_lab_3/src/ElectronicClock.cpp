#include "../headers/ElectronicClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

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

void ElectronicClock::displayHeader() const { Clock::displayHeader(); }

std::ostream &operator<<(std::ostream &os, const ElectronicClock &ec)
{
    os << std::left
       << std::setw(15) << ec.getBrand()
       << std::setw(15) << ec.getModel()
       << std::setw(8) << ec.getYear()
       << std::setw(15) << ec.getBatteryLife()
       << std::setw(18) << "-"
       << std::setw(15) << "-"
       << std::setw(12) << "-"
       << std::setw(15) << "-";
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

void ElectronicClock::edit()
{
    Clock::edit();

    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- ElectronicClock Additional Editing ---" << std::endl;
        std::cout << "1. Change Battery Life" << std::endl;
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
            std::cout << "Enter new battery life (hours): ";
            std::cin >> val;
            setBatteryLife(val);
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}
