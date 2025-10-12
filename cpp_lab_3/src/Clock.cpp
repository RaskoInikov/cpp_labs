#include "../headers/Clock.h"

// helpers
static int stringToInt(const String &s)
{
    int res = 0;
    bool neg = false;
    unsigned int i = 0;
    char c = s[i];
    if (c == '-')
    {
        neg = true;
        i = 1;
    }
    for (;; ++i)
    {
        c = s[i];
        if (c == '\0')
            break;
        if (c >= '0' && c <= '9')
            res = res * 10 + (c - '0');
        else
            break;
    }
    return neg ? -res : res;
}

// Clock implementation

Clock::Clock() : brand(), model(), year(0) {}

Clock::Clock(const String &brand_, const String &model_, int year_) : brand(brand_), model(model_), year(year_) {}

Clock::Clock(const Clock &other)
{
    *this = other;
}

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

void Clock::serialize(std::ostream &os) const
{
    os << "Brand: " << brand << '\n';
    os << "Model: " << model << '\n';
    os << "Year: " << year << '\n';
}

void Clock::deserialize(std::istream &is)
{
    // Read brand, model using String operator>>, then year via temporary String
    String tmp;
    std::cout << "Enter brand: ";
    is >> tmp;
    brand = tmp;

    std::cout << "Enter model: ";
    is >> tmp;
    model = tmp;

    std::cout << "Enter year: ";
    is >> tmp;
    year = stringToInt(tmp);
}

std::ostream &operator<<(std::ostream &os, const Clock &c)
{
    c.serialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, Clock &c)
{
    c.deserialize(is);
    return is;
}
