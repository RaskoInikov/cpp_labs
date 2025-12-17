#ifndef INTERFACE_TPP
#define INTERFACE_TPP

#include "../files/FileTxt.h"
#include "../files/FileBin.h"
#include "Interface.h"
#include "../headers/Clock.h"
#include "../headers/ElectronicClock.h"
#include "../headers/MechanicalClock.h"

#include <sstream>
#include <iomanip>

inline void Interface::clearInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline std::string Interface::readLineAllowEmpty()
{
    std::string s;
    std::getline(std::cin, s);
    return s;
}

inline int Interface::readIntAllowZero(const std::string &prompt)
{
    std::string line;
    std::cout << prompt << " (0 = skip): ";
    std::getline(std::cin, line);
    if (line.empty())
        return 0;
    try
    {
        return std::stoi(line);
    }
    catch (...)
    {
        return 0;
    }
}

template <typename U>
int Interface::cmp_by_brand(const U &a, const U &b)
{
    std::ostringstream sa, sb;
    sa << a.getBrand();
    sb << b.getBrand();
    int r = sa.str().compare(sb.str());
    if (r < 0)
        return -1;
    if (r > 0)
        return 1;
    return 0;
}

template <typename U>
int Interface::cmp_by_model(const U &a, const U &b)
{
    std::ostringstream sa, sb;
    sa << a.getModel();
    sb << b.getModel();
    int r = sa.str().compare(sb.str());
    if (r < 0)
        return -1;
    if (r > 0)
        return 1;
    return 0;
}

template <typename U>
int Interface::cmp_by_year(const U &a, const U &b)
{
    if (a.getYear() < b.getYear())
        return -1;
    if (a.getYear() > b.getYear())
        return 1;
    return 0;
}

template <typename FieldType>
bool Interface::match_field_string(const std::string &expected_std, const FieldType &actual_field) const
{
    if (expected_std.empty())
        return true;
    String expected(expected_std.c_str());
    return actual_field == expected;
}

inline bool Interface::match_field_int(int expected, int actual_field) const
{
    if (expected == 0)
        return true;
    return expected == actual_field;
}

template <typename U>
void Interface::configure_sorting_for_tree(TreeTemplate<U> &tree)
{
    std::cout << "Sort by:\n"
              << "1) Brand\n"
              << "2) Model\n"
              << "3) Year\n"
              << "Choice: ";

    int ch = 1;
    if (!(std::cin >> ch))
    {
        std::cin.clear();
        clearInputBuffer();
        ch = 1;
    }
    clearInputBuffer();

    if (ch == 1)
        tree.set_compare_func([](const U &x, const U &y)
                              { return Interface::cmp_by_brand<U>(x, y); });
    else if (ch == 2)
        tree.set_compare_func([](const U &x, const U &y)
                              { return Interface::cmp_by_model<U>(x, y); });
    else if (ch == 3)
        tree.set_compare_func([](const U &x, const U &y)
                              { return Interface::cmp_by_year<U>(x, y); });
    else
        tree.set_compare_func([](const U &x, const U &y)
                              { return Interface::cmp_by_brand<U>(x, y); });

    std::cout << "Comparator updated.\n";
}

template <typename U>
void Interface::search_by_fields(TreeTemplate<U> &tree)
{
    if (tree.empty())
    {
        std::cout << "Tree empty.\n";
        return;
    }

    std::cout << "\n=== Search (leave strings empty to skip, enter 0 for ints to skip) ===\n";

    std::string brand_line;
    std::cout << "Brand (Enter to skip): ";
    brand_line = readLineAllowEmpty();

    std::string model_line;
    std::cout << "Model (Enter to skip): ";
    model_line = readLineAllowEmpty();

    int year_val = readIntAllowZero("Year");

    std::string extra_str1, extra_str2;
    int extra_int1 = 0, extra_int2 = 0;

    if constexpr (std::is_same_v<U, SmartClock>)
    {
        extra_int1 = readIntAllowZero("Battery life (hours)");
        std::cout << "OS Version (Enter to skip): ";
        extra_str1 = readLineAllowEmpty();
    }
    else if constexpr (std::is_same_v<U, WallClock>)
    {
        extra_int1 = readIntAllowZero("Winding interval (days)");
        extra_int2 = readIntAllowZero("Diameter (mm)");
    }
    else if constexpr (std::is_same_v<U, WristClock>)
    {
        extra_int1 = readIntAllowZero("Winding interval (days)");
        extra_int2 = readIntAllowZero("Strap length (mm)");
    }

    bool found = false;

    std::function<void(Node<U> *)> visit = [&](Node<U> *node)
    {
        if (!node)
            return;
        visit(node->get_left());

        U *obj = node->get_data();
        if (obj)
        {
            bool ok = true;
            if (!match_field_string(brand_line, obj->getBrand()))
                ok = false;
            if (ok && !match_field_string(model_line, obj->getModel()))
                ok = false;
            if (ok && !match_field_int(year_val, obj->getYear()))
                ok = false;

            if (ok)
            {
                if constexpr (std::is_same_v<U, SmartClock>)
                {
                    if (!match_field_int(extra_int1, obj->getBatteryLife()))
                        ok = false;
                    if (ok && !match_field_string(extra_str1, obj->getOsVersion()))
                        ok = false;
                }
                else if constexpr (std::is_same_v<U, WallClock>)
                {
                    if (!match_field_int(extra_int1, obj->getWindingInterval()))
                        ok = false;
                    if (ok && !match_field_int(extra_int2, obj->getDiameter()))
                        ok = false;
                }
                else if constexpr (std::is_same_v<U, WristClock>)
                {
                    if (!match_field_int(extra_int1, obj->getWindingInterval()))
                        ok = false;
                    if (ok && !match_field_int(extra_int2, obj->getStrapLength()))
                        ok = false;
                }
            }

            if (ok)
            {
                if (!found)
                {
                    U tmp;
                    tmp.displayHeader();
                    std::cout << "\n";
                }

                std::cout << *obj << "\n";
                found = true;
            }
        }

        visit(node->get_right());
    };

    visit(tree.get_root());

    if (!found)
        std::cout << "No matches.\n";
    else
        std::cout << "\n";
}

template <typename U>
void Interface::tree_menu(TreeTemplate<U> &tree, const char *type_name)
{
    while (true)
    {
        std::cout << "\n--- " << type_name << " menu ---\n"
                                              "1 - Add\n"
                                              "2 - Delete\n"
                                              "3 - Search\n"
                                              "4 - Print\n"
                                              "5 - Save to text file\n"
                                              "6 - Load from text file\n"
                                              "7 - Save to binary file\n"
                                              "8 - Load from binary file\n"
                                              "0 - Back\n"
                                              "Choice: ";

        int cmd;
        if (!(std::cin >> cmd))
        {
            std::cin.clear();
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (cmd == 0)
            break;

        try
        {
            if (cmd == 1)
            {
                U *obj = new U();
                std::cin >> *obj;
                tree.Insert(obj);
            }
            else if (cmd == 2)
            {
                U temp;
                std::cin >> temp;
                tree.Delete(temp);
            }
            else if (cmd == 3)
                search_by_fields(tree);
            else if (cmd == 4)
                tree.Inorder();
            else if (cmd == 5)
                FileTxt<U>("data.txt", tree).save();
            else if (cmd == 6)
                FileTxt<U>("data.txt", tree).load();
            else if (cmd == 7)
                FileBin<U>("data.bin", tree).save();
            else if (cmd == 8)
                FileBin<U>("data.bin", tree).load();
        }
        catch (const std::exception &e)
        {
            std::cout << "File error: " << e.what() << "\n";
        }
    }
}

#endif