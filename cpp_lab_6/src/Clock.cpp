#include "../headers/Clock.h"
#include "../utils/string_utils.h"
#include <iostream>
#include <iomanip>
#include "../utils/error_utils.h"
#include <regex>
#include <cstring>

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
    return os;
}

std::istream &operator>>(std::istream &is, Clock &c)
{
    std::string s;

    s = checkEnglishMultiWord(is, "Enter brand: ");
    c.brand = String(s.c_str());

    s = checkEnglishMultiWord(is, "Enter model: ");
    c.model = String(s.c_str());

    std::cout << "Enter year: ";
    c.year = checkNumber(is, 1900, 2100);

    return is;
}

void Clock::displayHeader() const
{
    displayHeader(std::cout);
}

void Clock::displayHeader(std::ostream &os) const
{
    os << std::left
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

// ===== TEXT =====
void Clock::writeText(std::ostream &os) const
{
    os << std::left
       << std::setw(15) << brand
       << std::setw(15) << model
       << std::setw(8) << year;
}

void Clock::readText(std::istream &is)
{
    std::string b, m;
    int y;

    is >> b >> m >> y;
    brand = String(b.c_str());
    model = String(m.c_str());
    year = y;
}

// ===== BINARY =====

void Clock::writeBinary(std::ostream &os) const
{
    size_t len;

    len = std::strlen(brand.c_str());
    os.write(reinterpret_cast<const char *>(&len), sizeof(len));
    os.write(brand.c_str(), len);

    len = std::strlen(model.c_str());
    os.write(reinterpret_cast<const char *>(&len), sizeof(len));
    os.write(model.c_str(), len);

    os.write(reinterpret_cast<const char *>(&year), sizeof(year));
}

bool Clock::readBinary(std::istream &is)
{
    size_t len;
    char buffer[256];

    // brand
    if (!is.read(reinterpret_cast<char *>(&len), sizeof(len)))
        return false;
    if (len >= sizeof(buffer))
        return false;
    if (!is.read(buffer, len))
        return false;
    buffer[len] = '\0';
    brand = String(buffer);

    // model
    if (!is.read(reinterpret_cast<char *>(&len), sizeof(len)))
        return false;
    if (len >= sizeof(buffer))
        return false;
    if (!is.read(buffer, len))
        return false;
    buffer[len] = '\0';
    model = String(buffer);

    // year
    if (!is.read(reinterpret_cast<char *>(&year), sizeof(year)))
        return false;

    return true;
}