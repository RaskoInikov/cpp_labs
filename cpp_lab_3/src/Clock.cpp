#include "../headers/Clock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>

Clock::Clock() : brand(), model(), year(0) {}
Clock::Clock(const String &brand_, const String &model_, int year_) : brand(brand_), model(model_), year(year_) {}
Clock::Clock(const Clock &other) { *this = other; }

Clock &Clock::operator=(const Clock &other)
{
    if (this == &other)
        return *this;
    brand = other.brand;
    model = other.model;
    year = other.year;
    return *this;
}

String Clock::getBrand() const { return brand; }
void Clock::setBrand(const String &b) { brand = b; }
String Clock::getModel() const { return model; }
void Clock::setModel(const String &m) { model = m; }
int Clock::getYear() const { return year; }
void Clock::setYear(int y) { year = y; }

std::ostream &operator<<(std::ostream &os, const Clock &c)
{
    os << std::left
       << std::setw(15) << c.getBrand()
       << std::setw(15) << c.getModel()
       << std::setw(8) << c.getYear();
    //    << std::setw(15) << "-"
    //    << std::setw(18) << "-"
    //    << std::setw(15) << "-"
    //    << std::setw(12) << "-"
    //    << std::setw(15) << "-";
    return os;
}

std::istream &operator>>(std::istream &is, Clock &c)
{
    String tmp;
    std::cout << "Enter brand: ";
    is >> tmp;
    c.brand = tmp;

    std::cout << "Enter model: ";
    is >> tmp;
    c.model = tmp;

    std::cout << "Enter year: ";
    is >> tmp;
    c.year = stringToInt(tmp);
    return is;
}

void Clock::displayHeader() const
{
    std::cout << std::left
              << std::setw(15) << "Brand"
              << std::setw(15) << "Model"
              << std::setw(8) << "Year";
}

void Clock::edit()
{
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- Clock Base Edit ---" << std::endl;
        std::cout << "1. Change Brand\n2. Change Model\n3. Change Year\n0. Next" << std::endl;
        handleUserInput(choice);

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
        case 0:
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}
