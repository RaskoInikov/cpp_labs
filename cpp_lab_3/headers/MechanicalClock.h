#ifndef MECHANICAL_CLOCK_H
#define MECHANICAL_CLOCK_H

#include "../../string/string.h"
#include "Clock.h"
#include <iostream>

class MechanicalClock : virtual public Clock
{
private:
    int windingInterval; // days between windings

public:
    MechanicalClock();
    MechanicalClock(const String &brand, const String &model, int year, int windingInterval);
    MechanicalClock(const MechanicalClock &other);
    virtual ~MechanicalClock();

    MechanicalClock &operator=(const MechanicalClock &other);

    // getters / setters
    int getWindingInterval() const;
    void setWindingInterval(int days);

    // override serialization/deserialization
    void serialize(std::ostream &os) const override;
    void deserialize(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const MechanicalClock &mc);
    friend std::istream &operator>>(std::istream &is, MechanicalClock &mc);
};

#endif
