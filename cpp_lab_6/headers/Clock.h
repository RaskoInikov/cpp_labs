#ifndef CLOCK_H
#define CLOCK_H

#include "../../string/string.h"
#include <iostream>

class Clock
{
protected:
    String brand;
    String model;
    int year;

public:
    Clock();
    Clock(const String &brand, const String &model, int year);
    Clock(const Clock &other);
    virtual ~Clock() = default;

    Clock &operator=(const Clock &other);

    String getBrand() const;
    String getModel() const;
    int getYear() const;

    void setBrand(const String &b);
    void setModel(const String &m);
    void setYear(int y);

    virtual void displayHeader() const = 0;
    virtual void displayHeader(std::ostream &os) const;

    virtual void edit() = 0;

    virtual void writeText(std::ostream &os) const;
    virtual void readText(std::istream &is);

    virtual void writeBinary(std::ostream &os) const;
    virtual bool readBinary(std::istream &is);

    friend std::ostream &operator<<(std::ostream &os, const Clock &c);
    friend std::istream &operator>>(std::istream &is, Clock &c);
};

#endif
