#ifndef WRIST_CLOCK_H
#define WRIST_CLOCK_H

#include "../../string/string.h"
#include "MechanicalClock.h"
#include <iostream>

class WristClock : public MechanicalClock
{
private:
    int strapLength;

public:
    WristClock();
    WristClock(const String &brand, const String &model, int year, int windingInterval, int strapLength);
    WristClock(const WristClock &other);
    virtual ~WristClock() = default;

    WristClock &operator=(const WristClock &other);

    int getStrapLength() const;
    void setStrapLength(int mm);

    virtual void displayHeader() const override;
    virtual void edit() override;

    void writeText(std::ostream &os) const override;
    void readText(std::istream &is) override;

    void writeBinary(std::ostream &os) const override;
    bool readBinary(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const WristClock &wc);
    friend std::istream &operator>>(std::istream &is, WristClock &wc);
};

#endif
