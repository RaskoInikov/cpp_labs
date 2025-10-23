#ifndef CLOCK_H
#define CLOCK_H

#include "../../string/string.h"
#include <iostream>

class Clock
{
private:
    String brand;
    String model;
    int year;

public:
    Clock();
    Clock(const String &brand, const String &model, int year);
    Clock(const Clock &other);
    virtual ~Clock();

    Clock &operator=(const Clock &other);

    String getBrand() const;
    void setBrand(const String &b);
    String getModel() const;
    void setModel(const String &m);
    int getYear() const;
    void setYear(int y);

    virtual void displayHeader() const;

    friend std::ostream &operator<<(std::ostream &os, const Clock &c);
    friend std::istream &operator>>(std::istream &is, Clock &c);
};

#endif
