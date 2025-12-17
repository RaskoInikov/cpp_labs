#ifndef WALL_CLOCK_H
#define WALL_CLOCK_H

#include "../../string/string.h"
#include "MechanicalClock.h"
#include <iostream>

class WallClock : public MechanicalClock
{
private:
    int diameter;

public:
    WallClock();
    WallClock(const String &brand, const String &model, int year, int windingInterval, int diameter);
    WallClock(const WallClock &other);
    virtual ~WallClock() = default;

    WallClock &operator=(const WallClock &other);

    int getDiameter() const;
    void setDiameter(int mm);

    virtual void displayHeader() const override;
    virtual void edit() override;

    void writeText(std::ostream &os) const override;
    void readText(std::istream &is) override;

    void writeBinary(std::ostream &os) const override;
    bool readBinary(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const WallClock &wc);
    friend std::istream &operator>>(std::istream &is, WallClock &wc);
};

#endif
