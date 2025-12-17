#include "../headers/MechanicalClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>
#include "../utils/error_utils.h"
#include <regex>

MechanicalClock::MechanicalClock() : Clock(), windingInterval(0) {}
MechanicalClock::MechanicalClock(const String &brand, const String &model, int year, int windingInterval)
    : Clock(brand, model, year), windingInterval(windingInterval) {}
MechanicalClock::MechanicalClock(const MechanicalClock &other) { *this = other; }

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

void MechanicalClock::displayHeader() const
{
    Clock::displayHeader();
    std::cout << std::left
              << std::setw(18) << "Winding Interval";
}

std::ostream &operator<<(std::ostream &os, const MechanicalClock &mc)
{
    os << static_cast<const Clock &>(mc);
    os << std::left
       << std::setw(18) << mc.getWindingInterval();
    return os;
}

std::istream &operator>>(std::istream &is, MechanicalClock &mc)
{
    is >> static_cast<Clock &>(mc);

    std::cout << "Enter winding interval (days): ";
    mc.windingInterval = checkNumber(is, 1, 365);

    return is;
}

void MechanicalClock::edit()
{
    Clock::edit();
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- MechanicalClock Edit ---\n1. Change Winding Interval\n0. Next" << std::endl;
        handleUserInput(choice);

        int val;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new winding interval (days): ";
            std::cin >> val;
            setWindingInterval(val);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

void MechanicalClock::writeText(std::ostream &os) const
{
    Clock::writeText(os);
    os << std::setw(18) << windingInterval;
}

void MechanicalClock::readText(std::istream &is)
{
    Clock::readText(is);
    is >> windingInterval;
}

void MechanicalClock::writeBinary(std::ostream &os) const
{
    Clock::writeBinary(os);

    char buf[sizeof(windingInterval)];
    std::memcpy(buf, &windingInterval, sizeof(windingInterval));
    os.write(buf, sizeof(windingInterval));
}

bool MechanicalClock::readBinary(std::istream &is)
{
    if (!Clock::readBinary(is))
        return false;

    char buf[sizeof(windingInterval)];
    if (!is.read(buf, sizeof(windingInterval)))
        return false;
    std::memcpy(&windingInterval, buf, sizeof(windingInterval));

    return true;
}
