#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>

template <class T>
class BinarySearchTree;

template <class T>
class Iterator
{
private:
    typename BinarySearchTree<T>::Node *current;
    std::stack<typename BinarySearchTree<T>::Node *> stackNodes;

    void pushLeft(typename BinarySearchTree<T>::Node *node);

public:
    Iterator(typename BinarySearchTree<T>::Node *root = nullptr);
    Iterator &operator++(); // итерация вправо
    Iterator &operator--(); // итерация влево
    T &operator*() const;
    bool operator!=(const Iterator &other) const;
    bool operator==(const Iterator &other) const;

    friend class BinarySearchTree<T>;
};

#include "Iterator.tpp"

#endif // ITERATOR_H
