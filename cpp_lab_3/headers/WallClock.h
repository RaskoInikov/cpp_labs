#ifndef WALL_CLOCK_H
#define WALL_CLOCK_H

#include "../../string/string.h"
#include "MechanicalClock.h"
#include <iostream>

class WallClock : public MechanicalClock
{
private:
    int diameter; // mm

public:
    WallClock();
    WallClock(const String &brand, const String &model, int year, int windingInterval, int diameter);
    WallClock(const WallClock &other);
    virtual ~WallClock();

    WallClock &operator=(const WallClock &other);

    // getters / setters
    int getDiameter() const;
    void setDiameter(int mm);

    // override serialization/deserialization
    void serialize(std::ostream &os) const override;
    void deserialize(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const WallClock &wc);
    friend std::istream &operator>>(std::istream &is, WallClock &wc);
};

#endif
