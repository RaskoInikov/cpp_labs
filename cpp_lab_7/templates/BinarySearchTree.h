#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <functional>
#include <list>
#include <iostream>

template <class T>
class TreeIterator;

template <class T>
class BinarySearchTree
{
public:
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        Node *parent;
        explicit Node(const T &d)
            : data(d), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    Node *root;
    std::function<bool(const T &, const T &)> cmp;

    Node *findMin(Node *node) const;
    Node *insertNode(Node *node, Node *parent, const T &value);
    Node *removeNode(Node *node, const T &value);
    void clearNode(Node *node);

public:
    BinarySearchTree();
    explicit BinarySearchTree(std::function<bool(const T &, const T &)> comparator);
    ~BinarySearchTree();

    void setComparator(std::function<bool(const T &, const T &)> comparator);

    void add(const T &value);
    void remove(const T &value);
    void clear();

    void print() const;
    void inorderVisit(std::function<void(const T &)> visitor) const;

    std::list<T> toList() const;
    std::list<T> search(std::function<bool(const T &)> predicate) const;
};

#include "BinarySearchTree.tpp"
#endif
