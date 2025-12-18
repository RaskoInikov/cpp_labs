#ifndef REFLECTION_H
#define REFLECTION_H

#include <list>
#include <string>
#include <functional>

#include "../../string/string.h"

#include "../headers/Clock.h"
#include "../headers/ElectronicClock.h"
#include "../headers/MechanicalClock.h"
#include "../headers/SmartClock.h"
#include "../headers/WallClock.h"
#include "../headers/WristClock.h"

enum class FieldType
{
    STR,
    INT
};

template <typename T>
struct FieldDescriptor
{
    int id;
    std::string name;
    FieldType type;
    std::function<String(const T &)> getStr;
    std::function<int(const T &)> getInt;
};

/* ===== BASE CLOCK FIELDS ===== */

template <typename T>
struct ReflectionBase
{
    static std::list<FieldDescriptor<T>> baseFields()
    {
        return {
            {1, "Brand", FieldType::STR, [](const T &o)
             { return o.getBrand(); },
             {}},

            {2, "Model", FieldType::STR, [](const T &o)
             { return o.getModel(); },
             {}},

            {3, "Year", FieldType::INT, {}, [](const T &o)
             { return o.getYear(); }}};
    }
};

/* ===== GENERIC (EMPTY) ===== */

template <typename T>
struct Reflection
{
    static std::list<FieldDescriptor<T>> fields()
    {
        return {};
    }
};

/* ===== ELECTRONIC CLOCK ===== */

template <>
struct Reflection<ElectronicClock> : ReflectionBase<ElectronicClock>
{
    static std::list<FieldDescriptor<ElectronicClock>> fields()
    {
        auto f = baseFields();
        f.push_back({4, "BatteryLife", FieldType::INT, {}, [](const ElectronicClock &o)
                     { return o.getBatteryLife(); }});
        return f;
    }
};

/* ===== MECHANICAL CLOCK ===== */

template <>
struct Reflection<MechanicalClock> : ReflectionBase<MechanicalClock>
{
    static std::list<FieldDescriptor<MechanicalClock>> fields()
    {
        auto f = baseFields();
        f.push_back({4, "WindingInterval", FieldType::INT, {}, [](const MechanicalClock &o)
                     { return o.getWindingInterval(); }});
        return f;
    }
};

/* ===== SMART CLOCK ===== */

template <>
struct Reflection<SmartClock> : ReflectionBase<SmartClock>
{
    static std::list<FieldDescriptor<SmartClock>> fields()
    {
        auto f = baseFields();

        f.push_back({4, "BatteryLife", FieldType::INT, {}, [](const SmartClock &o)
                     { return o.getBatteryLife(); }});

        f.push_back({5, "OSVersion", FieldType::STR, [](const SmartClock &o)
                     { return o.getOsVersion(); },
                     {}});

        return f;
    }
};

/* ===== WALL CLOCK ===== */

template <>
struct Reflection<WallClock> : ReflectionBase<WallClock>
{
    static std::list<FieldDescriptor<WallClock>> fields()
    {
        auto f = baseFields();

        f.push_back({4, "WindingInterval", FieldType::INT, {}, [](const WallClock &o)
                     { return o.getWindingInterval(); }});

        f.push_back({5, "Diameter", FieldType::INT, {}, [](const WallClock &o)
                     { return o.getDiameter(); }});

        return f;
    }
};

/* ===== WRIST CLOCK ===== */

template <>
struct Reflection<WristClock> : ReflectionBase<WristClock>
{
    static std::list<FieldDescriptor<WristClock>> fields()
    {
        auto f = baseFields();

        f.push_back({4, "WindingInterval", FieldType::INT, {}, [](const WristClock &o)
                     { return o.getWindingInterval(); }});

        f.push_back({5, "StrapLength", FieldType::INT, {}, [](const WristClock &o)
                     { return o.getStrapLength(); }});

        return f;
    }
};

#endif // REFLECTION_H
