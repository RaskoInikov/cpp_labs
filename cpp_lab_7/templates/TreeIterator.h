#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include <iterator>

template <class T>
class BinarySearchTree;

template <class T>
class TreeIterator
{
public:
    using Node = typename BinarySearchTree<T>::Node;

private:
    Node *current;
    const BinarySearchTree<T> *tree;

public:
    explicit TreeIterator(Node *start = nullptr, const BinarySearchTree<T> *t = nullptr) : current(start), tree(t) {}
    TreeIterator &operator++();
    TreeIterator operator++(int)
    {
        TreeIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    TreeIterator &operator--();
    TreeIterator operator--(int)
    {
        TreeIterator tmp = *this;
        --(*this);
        return tmp;
    }

    T &operator*() const { return current->data; }
    T *operator->() const { return &current->data; }
    bool operator==(const TreeIterator &o) const { return current == o.current; }
    bool operator!=(const TreeIterator &o) const { return !(*this == o); }

    friend class BinarySearchTree<T>;
};

#include "TreeIterator.tpp"
#endif // TREEITERATOR_H
