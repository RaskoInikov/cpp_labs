#include "../headers/ElectronicClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

ElectronicClock::ElectronicClock() : Clock(), batteryLife(0) {}
ElectronicClock::ElectronicClock(const String &brand, const String &model, int year, int batteryLife)
    : Clock(brand, model, year), batteryLife(batteryLife) {}
ElectronicClock::ElectronicClock(const ElectronicClock &other) { *this = other; }

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

void ElectronicClock::displayHeader() const
{
    Clock::displayHeader();
    std::cout << std::left
              << std::setw(15) << "Battery Life";
}

std::ostream &operator<<(std::ostream &os, const ElectronicClock &ec)
{
    os << static_cast<const Clock &>(ec);
    os << std::left
       << std::setw(15) << ec.getBatteryLife();
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
        std::cout << "\n--- ElectronicClock Edit ---\n1. Change Battery Life\n0. Next" << std::endl;
        handleUserInput(choice);

        int val;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new battery life (hours): ";
            std::cin >> val;
            setBatteryLife(val);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}
