#include "../headers/WristClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>
#include "../utils/error_utils.h"
#include <regex>

WristClock::WristClock() : MechanicalClock(), strapLength(0) {}
WristClock::WristClock(const String &brand, const String &model, int year, int windingInterval, int strapLength)
    : MechanicalClock(brand, model, year, windingInterval), strapLength(strapLength) {}
WristClock::WristClock(const WristClock &other) { *this = other; }

WristClock &WristClock::operator=(const WristClock &other)
{
    if (this == &other)
        return *this;
    MechanicalClock::operator=(other);
    strapLength = other.strapLength;
    return *this;
}

int WristClock::getStrapLength() const { return strapLength; }
void WristClock::setStrapLength(int mm) { strapLength = mm; }

void WristClock::displayHeader() const
{
    MechanicalClock::displayHeader();
    std::cout << std::left
              << std::setw(15) << "Strap Length";
}

std::ostream &operator<<(std::ostream &os, const WristClock &wc)
{
    os << static_cast<const MechanicalClock &>(wc);
    os << std::left
       << std::setw(15) << wc.getStrapLength();
    return os;
}

std::istream &operator>>(std::istream &is, WristClock &wc)
{
    is >> static_cast<MechanicalClock &>(wc);

    std::cout << "Enter strap length (mm): ";
    wc.strapLength = checkNumber(is, 50, 300);

    return is;
}

void WristClock::edit()
{
    MechanicalClock::edit();
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- WristClock Edit ---\n1. Change Strap Length\n0. Done" << std::endl;
        handleUserInput(choice);

        int val;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new strap length (mm): ";
            std::cin >> val;
            setStrapLength(val);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

void WristClock::writeText(std::ostream &os) const
{
    MechanicalClock::writeText(os);
    os << std::setw(15) << strapLength;
}

void WristClock::readText(std::istream &is)
{
    MechanicalClock::readText(is);
    is >> strapLength;
}

void WristClock::writeBinary(std::ostream &os) const
{
    MechanicalClock::writeBinary(os);

    char buf[sizeof(strapLength)];
    std::memcpy(buf, &strapLength, sizeof(strapLength));
    os.write(buf, sizeof(strapLength));
}

bool WristClock::readBinary(std::istream &is)
{
    if (!MechanicalClock::readBinary(is))
        return false;

    char buf[sizeof(strapLength)];
    if (!is.read(buf, sizeof(strapLength)))
        return false;
    std::memcpy(&strapLength, buf, sizeof(strapLength));

    return true;
}
