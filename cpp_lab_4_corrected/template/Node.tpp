#pragma once
#ifndef NODE_TPP
#define NODE_TPP

#include <cstddef>

template <typename T>
Node<T>::Node()
    : data(nullptr), left(nullptr), right(nullptr), parent(nullptr)
{
}

template <typename T>
Node<T>::Node(T *d, Node<T> *l, Node<T> *r, Node<T> *p)
    : data(d), left(l), right(r), parent(p)
{
    if (left)
        left->parent = this;
    if (right)
        right->parent = this;
}

template <typename T>
Node<T>::~Node()
{
    // Node не удаляет data — это делает TreeTemplate::clear()
    data = nullptr;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template <typename T>
void Node<T>::set_left(Node<T> *node)
{
    left = node;
    if (node)
        node->parent = this;
}

template <typename T>
void Node<T>::set_right(Node<T> *node)
{
    right = node;
    if (node)
        node->parent = this;
}

template <typename T>
void Node<T>::set_data(T *d)
{
    data = d;
}

template <typename T>
void Node<T>::set_parent(Node<T> *p)
{
    parent = p;
}

template <typename T>
T *Node<T>::get_data() const
{
    return data;
}

template <typename T>
Node<T> *Node<T>::get_left() const
{
    return left;
}

template <typename T>
Node<T> *Node<T>::get_right() const
{
    return right;
}

template <typename T>
Node<T> *Node<T>::get_parent() const
{
    return parent;
}

#endif // NODE_TPP
