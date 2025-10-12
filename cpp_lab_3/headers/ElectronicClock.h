#ifndef ELECTRONIC_CLOCK_H
#define ELECTRONIC_CLOCK_H

#include "../../string/string.h"
#include "Clock.h"
#include <iostream>

class ElectronicClock : virtual public Clock
{
private:
    int batteryLife;

public:
    ElectronicClock();
    ElectronicClock(const String &brand, const String &model, int year, int batteryLife);
    ElectronicClock(const ElectronicClock &other);
    virtual ~ElectronicClock();

    ElectronicClock &operator=(const ElectronicClock &other);

    int getBatteryLife() const;
    void setBatteryLife(int hours);

    friend std::ostream &operator<<(std::ostream &os, const ElectronicClock &ec);
    friend std::istream &operator>>(std::istream &is, ElectronicClock &ec);
};

#endif
