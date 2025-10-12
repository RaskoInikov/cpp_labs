#ifndef ELECTRONIC_CLOCK_H
#define ELECTRONIC_CLOCK_H

#include "../../string/string.h"
#include "Clock.h"
#include <iostream>

class ElectronicClock : virtual public Clock
{
private:
    int batteryLife; // hours of battery life

public:
    ElectronicClock();
    ElectronicClock(const String &brand, const String &model, int year, int batteryLife);
    ElectronicClock(const ElectronicClock &other);
    virtual ~ElectronicClock();

    ElectronicClock &operator=(const ElectronicClock &other);

    // getters / setters
    int getBatteryLife() const;
    void setBatteryLife(int hours);

    // override serialization/deserialization
    void serialize(std::ostream &os) const override;
    void deserialize(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const ElectronicClock &ec);
    friend std::istream &operator>>(std::istream &is, ElectronicClock &ec);
};

#endif
