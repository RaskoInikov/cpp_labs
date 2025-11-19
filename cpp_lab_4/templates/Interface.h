#ifndef INTERFACE_TPL_H
#define INTERFACE_TPL_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <limits>
#include "BinarySearchTree.h"
#include "Reflection.h"

template <typename T>
class Interface
{
private:
    BinarySearchTree<T> tree;
    std::string name; // display name for type
    // helper to read a line and split into ints
    static std::vector<int> parseFieldChoiceLine(const std::string &line);
    static void clearStdin();

    // helpers to build comparator and predicate using Reflection<T>
    using FD = FieldDescriptor<T>;
    static std::function<bool(const T &, const T &)> makeComparator(const std::vector<FD> &fields,
                                                                    const std::vector<int> &chosenIds);
    static std::function<bool(const T &)> makePredicate(const std::vector<FD> &fields,
                                                        const std::vector<int> &chosenIds,
                                                        const std::vector<std::string> &values);

public:
    explicit Interface(const std::string &name_);
    ~Interface() = default;

    void runMenu(); // main loop for this type
    void addInteractive();
    void removeInteractive();
    void printTree() const;
    void printList() const;
    void iterateInteractive();
    void sortInteractive();
    void searchInteractive();
};

#include "Interface.tpp"
#endif // INTERFACE_TPL_H
