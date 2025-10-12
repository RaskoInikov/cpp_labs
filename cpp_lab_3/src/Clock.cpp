#include "../headers/Clock.h"
#include "../utils/string_utils.h"
#include <iostream>

Clock::Clock() : brand(), model(), year(0) {}
Clock::Clock(const String &brand_, const String &model_, int year_) : brand(brand_), model(model_), year(year_) {}
Clock::Clock(const Clock &other) { *this = other; }
Clock::~Clock() {}

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
    os << "Brand: " << c.brand << '\n';
    os << "Model: " << c.model << '\n';
    os << "Year: " << c.year << '\n';
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
