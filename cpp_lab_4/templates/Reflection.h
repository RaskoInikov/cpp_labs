#ifndef REFLECTION_H
#define REFLECTION_H

#include <vector>
#include <string>
#include <functional>
#include <variant>
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

template <typename T>
struct ReflectionClockBase
{
    static std::vector<FieldDescriptor<T>> baseFields()
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

    static void append(std::vector<FieldDescriptor<T>> &v,
                       std::initializer_list<FieldDescriptor<T>> extra)
    {
        for (const FieldDescriptor<T> &e : extra)
            v.push_back(e);
    }
};

template <typename T>
struct Reflection
{
    static std::vector<FieldDescriptor<T>> fields()
    {
        return {};
    }
};

template <>
struct Reflection<ElectronicClock> : ReflectionClockBase<ElectronicClock>
{
    static std::vector<FieldDescriptor<ElectronicClock>> fields()
    {
        using T = ElectronicClock;
        std::vector<FieldDescriptor<T>> v = ReflectionClockBase<T>::baseFields();
        append(v, {{4, "BatteryLife", FieldType::INT, {}, [](const T &o)
                    { return o.getBatteryLife(); }}});
        return v;
    }
};

template <>
struct Reflection<MechanicalClock> : ReflectionClockBase<MechanicalClock>
{
    static std::vector<FieldDescriptor<MechanicalClock>> fields()
    {
        using T = MechanicalClock;
        std::vector<FieldDescriptor<T>> v = ReflectionClockBase<T>::baseFields();
        append(v, {{4, "WindingInterval", FieldType::INT, {}, [](const T &o)
                    { return o.getWindingInterval(); }}});
        return v;
    }
};

template <>
struct Reflection<SmartClock> : ReflectionClockBase<SmartClock>
{
    static std::vector<FieldDescriptor<SmartClock>> fields()
    {
        using T = SmartClock;
        std::vector<FieldDescriptor<T>> v = ReflectionClockBase<T>::baseFields();
        append(v, {{4, "BatteryLife", FieldType::INT, {}, [](const T &o)
                    { return o.getBatteryLife(); }},
                   {5, "OSVersion", FieldType::STR, [](const T &o)
                    { return o.getOsVersion(); },
                    {}}});
        return v;
    }
};

template <>
struct Reflection<WallClock> : ReflectionClockBase<WallClock>
{
    static std::vector<FieldDescriptor<WallClock>> fields()
    {
        using T = WallClock;
        std::vector<FieldDescriptor<T>> v = ReflectionClockBase<T>::baseFields();
        append(v, {{4, "WindingInterval", FieldType::INT, {}, [](const T &o)
                    { return o.getWindingInterval(); }},
                   {5, "Diameter", FieldType::INT, {}, [](const T &o)
                    { return o.getDiameter(); }}});
        return v;
    }
};

template <>
struct Reflection<WristClock> : ReflectionClockBase<WristClock>
{
    static std::vector<FieldDescriptor<WristClock>> fields()
    {
        using T = WristClock;
        std::vector<FieldDescriptor<T>> v = ReflectionClockBase<T>::baseFields();
        append(v, {{4, "WindingInterval", FieldType::INT, {}, [](const T &o)
                    { return o.getWindingInterval(); }},
                   {5, "StrapLength", FieldType::INT, {}, [](const T &o)
                    { return o.getStrapLength(); }}});
        return v;
    }
};

#endif // REFLECTION_H
