#include "../headers/WristClock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

WristClock::WristClock() : MechanicalClock(), strapLength(0) {}
WristClock::WristClock(const String &brand, const String &model, int year, int windingInterval, int strapLength)
    : Clock(brand, model, year), MechanicalClock(brand, model, year, windingInterval), strapLength(strapLength) {}
WristClock::WristClock(const WristClock &other) { *this = other; }
WristClock::~WristClock() {}

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

void WristClock::displayHeader() const { Clock::displayHeader(); }

std::ostream &operator<<(std::ostream &os, const WristClock &wc)
{
    os << std::left
       << std::setw(15) << wc.getBrand()
       << std::setw(15) << wc.getModel()
       << std::setw(8) << wc.getYear()
       << std::setw(15) << "-"
       << std::setw(18) << wc.getWindingInterval()
       << std::setw(15) << "-"
       << std::setw(12) << "-"
       << std::setw(15) << wc.getStrapLength();
    return os;
}

std::istream &operator>>(std::istream &is, WristClock &wc)
{
    is >> static_cast<MechanicalClock &>(wc);
    String tmp;
    std::cout << "Enter strap length (mm): ";
    is >> tmp;
    wc.strapLength = stringToInt(tmp);
    return is;
}

void WristClock::edit()
{
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- WristClock Menu ---" << std::endl;
        std::cout << "1. Change Brand" << std::endl;
        std::cout << "2. Change Model" << std::endl;
        std::cout << "3. Change Year" << std::endl;
        std::cout << "4. Change Winding Interval" << std::endl;
        std::cout << "5. Change Strap Length" << std::endl;
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
            std::cout << "Enter new winding interval (days): ";
            std::cin >> val;
            setWindingInterval(val);
            break;
        case 5:
            std::cout << "Enter new strap length (mm): ";
            std::cin >> val;
            setStrapLength(val);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }

        if (choice >= 1 && choice <= 5)
        {
            std::cout << "\n✅ Updated WristClock:" << std::endl;
            displayHeader();
            std::cout << *this << std::endl;
        }
    }
}
