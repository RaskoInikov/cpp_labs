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
    // constructors / destructor
    Clock();
    Clock(const String &brand, const String &model, int year);
    Clock(const Clock &other);
    virtual ~Clock();

    // assignment
    Clock &operator=(const Clock &other);

    // getters / setters
    String getBrand() const;
    void setBrand(const String &b);

    String getModel() const;
    void setModel(const String &m);

    int getYear() const;
    void setYear(int y);

    // serialization / deserialization (polymorphic)
    virtual void serialize(std::ostream &os) const;
    virtual void deserialize(std::istream &is);

    // streaming operators
    friend std::ostream &operator<<(std::ostream &os, const Clock &c);
    friend std::istream &operator>>(std::istream &is, Clock &c);
};

#endif
