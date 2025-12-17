#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include "TreeTemplate.h"
#include <iostream>
#include <string>
#include <limits>
#include <functional>
#include <type_traits>
#include <vector>

#include "../headers/SmartClock.h"
#include "../headers/WallClock.h"
#include "../headers/WristClock.h"

class Interface
{
public:
    enum class ClockType
    {
        NONE = 0,
        SMART = 1,
        WALL = 2,
        WRIST = 3
    };

private:
    TreeTemplate<SmartClock> smart_tree;
    TreeTemplate<WallClock> wall_tree;
    TreeTemplate<WristClock> wrist_tree;

    ClockType active_type;

    template <typename U>
    static int cmp_by_brand(const U &a, const U &b);

    template <typename U>
    static int cmp_by_model(const U &a, const U &b);

    template <typename U>
    static int cmp_by_year(const U &a, const U &b);

    void clearInputBuffer();
    std::string readLineAllowEmpty();
    int readIntAllowZero(const std::string &prompt);

    template <typename U>
    void configure_sorting_for_tree(TreeTemplate<U> &tree);

    template <typename U>
    void tree_menu(TreeTemplate<U> &tree, const char *type_name);

    template <typename U>
    void search_by_fields(TreeTemplate<U> &tree);

    template <typename FieldType>
    bool match_field_string(const std::string &expected_std, const FieldType &actual_field) const;

    bool match_field_int(int expected, int actual_field) const;

public:
    Interface();
    ~Interface();

    void menu();
};

#include "Interface.tpp"

#endif // INTERFACE_H