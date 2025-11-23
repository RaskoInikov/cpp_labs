#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <functional>
#include <vector>
#include <iostream>
#include <memory>
#include <optional>

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
        explicit Node(const T &d) : data(d), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    Node *root;
    std::function<bool(const T &, const T &)> cmp;

    Node *findMin(Node *node) const;
    Node *findMax(Node *node) const;

    Node *insertNode(Node *node, Node *parent, const T &value);
    Node *removeNode(Node *node, const T &value);
    void clearNode(Node *node);

public:
    using iterator = TreeIterator<T>;

    BinarySearchTree();
    explicit BinarySearchTree(std::function<bool(const T &, const T &)> comparator);
    ~BinarySearchTree();

    void setComparator(std::function<bool(const T &, const T &)> comparator);

    void add(const T &value);
    void remove(const T &value);
    void clear();

    iterator begin() const;
    iterator end() const;

    void print() const;
    void printNode(Node *node, const std::string &prefix, bool isRoot) const;
    void printList() const;
    void inorderVisit(std::function<void(const T &)> visitor) const;
    void buildFromVector(const std::vector<T> &v);

    std::vector<T> toVector() const;
    std::vector<T> search(std::function<bool(const T &)> predicate) const;

    friend class TreeIterator<T>;
};

#include "BinarySearchTree.tpp"
#endif // BINARYSEARCHTREE_H
