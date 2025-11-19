#ifndef REFLECTION_H
#define REFLECTION_H

#include <vector>
#include <string>
#include <functional>
#include <variant>
#include "../../string/string.h" // your String type

// Field type enum
enum class FieldType
{
    STR,
    INT
};

// Generic field descriptor for type T
template <typename T>
struct FieldDescriptor
{
    int id;
    std::string name;
    FieldType type;
    // getters: depending on type one of them is used
    std::function<String(const T &)> getStr;
    std::function<int(const T &)> getInt;
};

// Primary template - must be specialized for each concrete type
template <typename T>
struct Reflection
{
    static std::vector<FieldDescriptor<T>> fields();
};

// Forward declarations of clock classes - include their headers where you use Reflection
#include "../headers/Clock.h"
#include "../headers/ElectronicClock.h"
#include "../headers/MechanicalClock.h"
#include "../headers/SmartClock.h"
#include "../headers/WallClock.h"
#include "../headers/WristClock.h"

// Specializations:

// ElectronicClock: fields from Clock + batteryLife
template <>
struct Reflection<ElectronicClock>
{
    static std::vector<FieldDescriptor<ElectronicClock>> fields()
    {
        using T = ElectronicClock;
        return {
            {1, "Brand", FieldType::STR, [](const T &o)
             { return o.getBrand(); },
             {}},
            {2, "Model", FieldType::STR, [](const T &o)
             { return o.getModel(); },
             {}},
            {3, "Year", FieldType::INT, {}, [](const T &o)
             { return o.getYear(); }},
            {4, "BatteryLife", FieldType::INT, {}, [](const T &o)
             { return o.getBatteryLife(); }}};
    }
};

// MechanicalClock: Clock + windingInterval
template <>
struct Reflection<MechanicalClock>
{
    static std::vector<FieldDescriptor<MechanicalClock>> fields()
    {
        using T = MechanicalClock;
        return {
            {1, "Brand", FieldType::STR, [](const T &o)
             { return o.getBrand(); },
             {}},
            {2, "Model", FieldType::STR, [](const T &o)
             { return o.getModel(); },
             {}},
            {3, "Year", FieldType::INT, {}, [](const T &o)
             { return o.getYear(); }},
            {4, "WindingInterval", FieldType::INT, {}, [](const T &o)
             { return o.getWindingInterval(); }}};
    }
};

// SmartClock: ElectronicClock + osVersion
template <>
struct Reflection<SmartClock>
{
    static std::vector<FieldDescriptor<SmartClock>> fields()
    {
        using T = SmartClock;
        return {
            {1, "Brand", FieldType::STR, [](const T &o)
             { return o.getBrand(); },
             {}},
            {2, "Model", FieldType::STR, [](const T &o)
             { return o.getModel(); },
             {}},
            {3, "Year", FieldType::INT, {}, [](const T &o)
             { return o.getYear(); }},
            {4, "BatteryLife", FieldType::INT, {}, [](const T &o)
             { return o.getBatteryLife(); }},
            {5, "OSVersion", FieldType::STR, [](const T &o)
             { return o.getOsVersion(); },
             {}}};
    }
};

// WallClock: MechanicalClock + diameter
template <>
struct Reflection<WallClock>
{
    static std::vector<FieldDescriptor<WallClock>> fields()
    {
        using T = WallClock;
        return {
            {1, "Brand", FieldType::STR, [](const T &o)
             { return o.getBrand(); },
             {}},
            {2, "Model", FieldType::STR, [](const T &o)
             { return o.getModel(); },
             {}},
            {3, "Year", FieldType::INT, {}, [](const T &o)
             { return o.getYear(); }},
            {4, "WindingInterval", FieldType::INT, {}, [](const T &o)
             { return o.getWindingInterval(); }},
            {5, "Diameter", FieldType::INT, {}, [](const T &o)
             { return o.getDiameter(); }}};
    }
};

// WristClock: MechanicalClock + strapLength
template <>
struct Reflection<WristClock>
{
    static std::vector<FieldDescriptor<WristClock>> fields()
    {
        using T = WristClock;
        return {
            {1, "Brand", FieldType::STR, [](const T &o)
             { return o.getBrand(); },
             {}},
            {2, "Model", FieldType::STR, [](const T &o)
             { return o.getModel(); },
             {}},
            {3, "Year", FieldType::INT, {}, [](const T &o)
             { return o.getYear(); }},
            {4, "WindingInterval", FieldType::INT, {}, [](const T &o)
             { return o.getWindingInterval(); }},
            {5, "StrapLength", FieldType::INT, {}, [](const T &o)
             { return o.getStrapLength(); }}};
    }
};

#endif // REFLECTION_H
