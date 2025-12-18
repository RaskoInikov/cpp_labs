#ifndef INTERFACE_TPL_H
#define INTERFACE_TPL_H

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <functional>
#include <limits>

#include "BinarySearchTree.h"
#include "Reflection.h"
#include "Algorithms.h"

template <typename T>
class Interface
{
private:
    BinarySearchTree<T> tree;
    std::list<T> lst;
    bool listBuilt = false;

    std::string name;
    using FD = FieldDescriptor<T>;

    static void clearStdin();
    static std::list<int> parseFieldLine(const std::string &line);

    static std::function<bool(const T &, const T &)>
    makeComparator(const std::list<FD> &fields,
                   const std::list<int> &ids);

    static std::function<bool(const T &)>
    makePredicate(const std::list<FD> &fields,
                  const std::list<int> &ids,
                  const std::list<std::string> &values);

    /* ===== LIST FUNCTIONAL ===== */
    void buildListFromTree();
    void printList();
    void sortList();
    void searchInList();

public:
    explicit Interface(const std::string &name);
    void runMenu();

    void addInteractive();
    void removeInteractive();
    void printTree() const;
};

#include "Interface.tpp"
#endif
