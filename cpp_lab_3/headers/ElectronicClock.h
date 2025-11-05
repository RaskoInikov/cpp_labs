#ifndef ELECTRONIC_CLOCK_H
#define ELECTRONIC_CLOCK_H

#include "../../string/string.h"
#include "Clock.h"
#include <iostream>

class ElectronicClock : virtual public Clock
{
protected:
    int batteryLife;

public:
    ElectronicClock();
    ElectronicClock(const String &brand, const String &model, int year, int batteryLife);
    ElectronicClock(const ElectronicClock &other);
    virtual ~ElectronicClock() = default;

    ElectronicClock &operator=(const ElectronicClock &other);

    int getBatteryLife() const;
    void setBatteryLife(int hours);

    virtual void displayHeader() const override;
    virtual void edit() override;

    friend std::ostream &operator<<(std::ostream &os, const ElectronicClock &ec);
    friend std::istream &operator>>(std::istream &is, ElectronicClock &ec);
};

#endif
