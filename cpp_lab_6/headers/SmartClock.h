#ifndef SMART_CLOCK_H
#define SMART_CLOCK_H

#include "../../string/string.h"
#include "ElectronicClock.h"
#include <iostream>

class SmartClock : public ElectronicClock
{
private:
    String osVersion;

public:
    SmartClock();
    SmartClock(const String &brand, const String &model, int year, int batteryLife, const String &osVersion);
    SmartClock(const SmartClock &other);
    virtual ~SmartClock() = default;

    SmartClock &operator=(const SmartClock &other);

    String getOsVersion() const;
    void setOsVersion(const String &v);

    virtual void displayHeader() const override;
    virtual void edit() override;

    void writeText(std::ostream &os) const override;
    void readText(std::istream &is) override;

    void writeBinary(std::ostream &os) const override;
    bool readBinary(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const SmartClock &sc);
    friend std::istream &operator>>(std::istream &is, SmartClock &sc);
};

#endif
