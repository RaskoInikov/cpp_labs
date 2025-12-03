#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include "TreeTemplate.h"
#include <iostream>
#include <string>
#include <limits>

// часы
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

    // шаблонные компараторы — реализованы в Interface.tpp
    template <typename U>
    static int cmp_by_brand(const U &a, const U &b);
    template <typename U>
    static int cmp_by_model(const U &a, const U &b);
    template <typename U>
    static int cmp_by_year(const U &a, const U &b);

    // шаблонные методы управления деревом
    template <typename U>
    void configure_sorting_for_tree(TreeTemplate<U> &tree);

    template <typename U>
    void tree_menu(TreeTemplate<U> &tree, const char *type_name);

    template <typename U>
    void search_by_fields(TreeTemplate<U> &tree);

    // input helper (inline in tpp)
    static void clearInputBuffer();
    static std::string readLineAllowEmpty();

public:
    Interface();
    ~Interface();

    // не-шаблонный: реализован в Interface.cpp
    void menu();
};

// подключаем шаблонные реализации
#include "Interface.tpp"

#endif // INTERFACE_H
