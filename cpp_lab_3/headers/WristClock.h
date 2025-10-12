#ifndef WRIST_CLOCK_H
#define WRIST_CLOCK_H

#include "../../string/string.h"
#include "MechanicalClock.h"
#include <iostream>

class WristClock : public MechanicalClock
{
private:
    int strapLength; // mm

public:
    WristClock();
    WristClock(const String &brand, const String &model, int year, int windingInterval, int strapLength);
    WristClock(const WristClock &other);
    virtual ~WristClock();

    WristClock &operator=(const WristClock &other);

    // getters / setters
    int getStrapLength() const;
    void setStrapLength(int mm);

    // override serialization/deserialization
    void serialize(std::ostream &os) const override;
    void deserialize(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const WristClock &wc);
    friend std::istream &operator>>(std::istream &is, WristClock &wc);
};

#endif
