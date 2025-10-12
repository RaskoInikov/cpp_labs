#ifndef SMART_CLOCK_H
#define SMART_CLOCK_H

#include "../../string/string.h"
#include "ElectronicClock.h"
#include <iostream>

class SmartClock : public ElectronicClock
{
private:
    String osVersion; // single String field representing installed OS/version

public:
    SmartClock();
    SmartClock(const String &brand, const String &model, int year, int batteryLife, const String &osVersion);
    SmartClock(const SmartClock &other);
    virtual ~SmartClock();

    SmartClock &operator=(const SmartClock &other);

    // getters / setters
    String getOsVersion() const;
    void setOsVersion(const String &v);

    // override serialization/deserialization
    void serialize(std::ostream &os) const override;
    void deserialize(std::istream &is) override;

    friend std::ostream &operator<<(std::ostream &os, const SmartClock &sc);
    friend std::istream &operator>>(std::istream &is, SmartClock &sc);
};

#endif
