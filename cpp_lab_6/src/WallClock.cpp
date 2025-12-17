#include "../headers/WallClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>
#include "../utils/error_utils.h"
#include <regex>

WallClock::WallClock() : MechanicalClock(), diameter(0) {}
WallClock::WallClock(const String &brand, const String &model, int year, int windingInterval, int diameter)
    : MechanicalClock(brand, model, year, windingInterval), diameter(diameter) {}
WallClock::WallClock(const WallClock &other) { *this = other; }

WallClock &WallClock::operator=(const WallClock &other)
{
    if (this == &other)
        return *this;
    MechanicalClock::operator=(other);
    diameter = other.diameter;
    return *this;
}

int WallClock::getDiameter() const { return diameter; }
void WallClock::setDiameter(int mm) { diameter = mm; }

void WallClock::displayHeader() const
{
    MechanicalClock::displayHeader();
    std::cout << std::left
              << std::setw(12) << "Diameter";
}

std::ostream &operator<<(std::ostream &os, const WallClock &wc)
{
    os << static_cast<const MechanicalClock &>(wc);
    os << std::left
       << std::setw(12) << wc.getDiameter();
    return os;
}

std::istream &operator>>(std::istream &is, WallClock &wc)
{
    is >> static_cast<MechanicalClock &>(wc);

    std::cout << "Enter diameter (mm): ";
    wc.diameter = checkNumber(is, 50, 2000);

    return is;
}

void WallClock::edit()
{
    MechanicalClock::edit();
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- WallClock Edit ---\n1. Change Diameter\n0. Done" << std::endl;
        handleUserInput(choice);

        int val;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new diameter (mm): ";
            std::cin >> val;
            setDiameter(val);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

void WallClock::writeText(std::ostream &os) const
{
    MechanicalClock::writeText(os);
    os << std::setw(12) << diameter;
}

void WallClock::readText(std::istream &is)
{
    MechanicalClock::readText(is);
    is >> diameter;
}

void WallClock::writeBinary(std::ostream &os) const
{
    MechanicalClock::writeBinary(os);
    os.write(reinterpret_cast<const char *>(&diameter), sizeof(diameter));
}

bool WallClock::readBinary(std::istream &is)
{
    if (!MechanicalClock::readBinary(is))
        return false;

    if (!is.read(reinterpret_cast<char *>(&diameter), sizeof(diameter)))
        return false;

    return true;
}
