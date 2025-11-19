#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Reflection.h"
#include "BinarySearchTree.h"
#include <limits>

template <typename T>
Interface<T>::Interface(const std::string &name_) : tree(), name(name_)
{
    // Build a default comparator from all available fields (in the order they are defined)
    auto fields = Reflection<T>::fields();
    std::vector<int> defaultIds;
    for (const auto &f : fields)
        defaultIds.push_back(f.id);
    if (!fields.empty())
    {
        auto defaultCmp = Interface<T>::makeComparator(fields, defaultIds);
        tree.setComparator(defaultCmp);
    }
}

template <typename T>
void Interface<T>::clearStdin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
std::vector<int> Interface<T>::parseFieldChoiceLine(const std::string &line)
{
    std::istringstream iss(line);
    std::vector<int> ids;
    int x;
    while (iss >> x)
    {
        ids.push_back(x);
    }
    return ids;
}

template <typename T>
std::function<bool(const T &, const T &)> Interface<T>::makeComparator(const std::vector<FD> &fields,
                                                                       const std::vector<int> &chosenIds)
{
    return [fields, chosenIds](const T &a, const T &b) -> bool
    {
        for (int id : chosenIds)
        {
            auto it = std::find_if(fields.begin(), fields.end(), [&](const FD &f)
                                   { return f.id == id; });
            if (it == fields.end())
                continue;
            if (it->type == FieldType::STR)
            {
                String sa = it->getStr(a);
                String sb = it->getStr(b);
                // use String::operator< for ordering
                if (sa < sb)
                    return true;
                if (sb < sa)
                    return false;
            }
            else
            { // INT
                int ia = it->getInt(a);
                int ib = it->getInt(b);
                if (ia < ib)
                    return true;
                if (ib < ia)
                    return false;
            }
        }
        return false;
    };
}

template <typename T>
std::function<bool(const T &)> Interface<T>::makePredicate(const std::vector<FD> &fields,
                                                           const std::vector<int> &chosenIds,
                                                           const std::vector<std::string> &values)
{
    return [fields, chosenIds, values](const T &obj) -> bool
    {
        for (size_t i = 0; i < chosenIds.size(); ++i)
        {
            int id = chosenIds[i];
            std::string q = values[i];
            auto it = std::find_if(fields.begin(), fields.end(), [&](const FD &f)
                                   { return f.id == id; });
            if (it == fields.end())
                continue;
            if (it->type == FieldType::STR)
            {
                String s = it->getStr(obj);
                // Compare String and std::string by using c_str()
                if (!(std::string(s.c_str()) == q))
                    return false;
            }
            else
            {
                try
                {
                    int qi = std::stoi(q);
                    if (it->getInt(obj) != qi)
                        return false;
                }
                catch (...)
                {
                    return false;
                }
            }
        }
        return true;
    };
}

template <typename T>
void Interface<T>::addInteractive()
{
    T obj;
    std::cout << "Enter new " << name << " fields:\n";
    std::cin >> obj; // uses operator>>
    tree.add(obj);
    std::cout << "Added.\n";
}

template <typename T>
void Interface<T>::removeInteractive()
{
    std::cout << "Remove: provide full object fields (operator>> will be used).\n";
    T key;
    std::cin >> key;
    // removal uses the tree comparator previously set in constructor
    tree.remove(key);
    std::cout << "Remove attempted (if existed, removed).\n";
}

template <typename T>
void Interface<T>::printTree() const
{
    std::cout << "=== " << name << " tree ===\n";
    tree.print();
    std::cout << "=========================\n";
}

template <typename T>
void Interface<T>::iterateInteractive()
{
    std::cout << "Iterating forward (press Enter to step; type 'q' then Enter to quit):\n";
    auto it = tree.begin();
    auto endIt = tree.end();
    std::string line;
    std::getline(std::cin, line); // flush
    while (it != endIt)
    {
        std::cout << *it << "\n";
        std::getline(std::cin, line);
        if (line == "q")
            break;
        ++it;
    }
    std::cout << "Iteration finished.\n";
}

template <typename T>
void Interface<T>::sortInteractive()
{
    auto fields = Reflection<T>::fields();
    if (fields.empty())
    {
        std::cout << "No fields available for sorting.\n";
        return;
    }
    std::cout << "Sort by fields (type numbers separated by spaces):\n";
    for (const auto &f : fields)
    {
        std::cout << f.id << ") " << f.name << (f.type == FieldType::STR ? " (string)" : " (int)") << "\n";
    }
    std::cout << "Enter field ids (e.g. \"1 3\"): ";
    clearStdin();
    std::string line;
    std::getline(std::cin, line);
    auto chosen = parseFieldChoiceLine(line);
    if (chosen.empty())
    {
        std::cout << "No fields chosen.\n";
        return;
    }

    // build comparator using chosen fields
    auto cmp = makeComparator(fields, chosen);

    // get vector, sort, rebuild tree
    auto vec = tree.toVector();
    std::stable_sort(vec.begin(), vec.end(), cmp);

    // set comparator and rebuild tree
    tree.clear();
    tree.setComparator(cmp);
    tree.buildFromVector(vec);

    std::cout << "Sorted by selected fields.\n";
}

template <typename T>
void Interface<T>::searchInteractive()
{
    auto fields = Reflection<T>::fields();
    if (fields.empty())
    {
        std::cout << "No searchable fields.\n";
        return;
    }
    std::cout << "Search by fields (enter numbers separated by spaces):\n";
    for (const auto &f : fields)
    {
        std::cout << f.id << ") " << f.name << (f.type == FieldType::STR ? " (string)" : " (int)") << "\n";
    }
    std::cout << "Enter field ids (e.g. \"1 2\"): ";
    clearStdin();
    std::string line;
    std::getline(std::cin, line);
    auto chosen = parseFieldChoiceLine(line);
    if (chosen.empty())
    {
        std::cout << "No fields chosen.\n";
        return;
    }

    std::vector<std::string> values;
    values.reserve(chosen.size());
    for (int id : chosen)
    {
        auto it = std::find_if(fields.begin(), fields.end(), [&](const FD &f)
                               { return f.id == id; });
        if (it == fields.end())
        {
            values.push_back("");
            continue;
        }
        std::string prompt = "Enter value for " + it->name + ": ";
        std::cout << prompt;
        std::string val;
        std::getline(std::cin, val);
        if (val.empty())
        {
            std::cout << "Empty value, aborting search.\n";
            return;
        }
        values.push_back(val);
    }

    auto pred = makePredicate(fields, chosen, values);
    auto found = tree.search(pred);
    if (found.empty())
    {
        std::cout << "Nothing found.\n";
    }
    else
    {
        std::cout << "Found " << found.size() << " result(s):\n";
        T s;
        s.displayHeader();
        std::cout << "\n";
        for (const auto &r : found)
        {
            std::cout << r << "\n";
        }
    }
}

template <typename T>
void Interface<T>::runMenu()
{
    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n--- " << name << " Tree Menu ---\n";
        std::cout << "1. Add " << name << "\n";
        std::cout << "2. Remove " << name << "\n";
        std::cout << "3. Print tree\n";
        std::cout << "4. Search\n";
        std::cout << "5. Sort\n";
        std::cout << "6. Iterate\n";
        std::cout << "0. Back to type selection\n";
        std::cout << "Choice: ";
        if (!(std::cin >> choice))
        {
            clearStdin();
            std::cout << "Invalid input.\n";
            choice = -1;
            continue;
        }
        clearStdin();
        switch (choice)
        {
        case 1:
            addInteractive();
            break;
        case 2:
            removeInteractive();
            break;
        case 3:
            printTree();
            break;
        case 4:
            searchInteractive();
            break;
        case 5:
            sortInteractive();
            break;
        case 6:
            iterateInteractive();
            break;
        case 0:
            std::cout << "Returning to main menu.\n";
            break;
        default:
            std::cout << "Unknown option.\n";
            break;
        }
    }
}
