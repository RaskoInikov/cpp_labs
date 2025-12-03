#pragma once
#ifndef NODE_H
#define NODE_H

// Простая декларация шаблонного узла — реализация в Node.tpp

template <typename T>
struct Node
{
    T *data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;

    Node();
    explicit Node(T *d, Node<T> *l = nullptr, Node<T> *r = nullptr, Node<T> *p = nullptr);
    ~Node();

    void set_left(Node<T> *node);
    void set_right(Node<T> *node);
    void set_data(T *d);
    void set_parent(Node<T> *p);

    T *get_data() const;
    Node<T> *get_left() const;
    Node<T> *get_right() const;
    Node<T> *get_parent() const;
};

// подключаем реализацию
#include "Node.tpp"

#endif // NODE_H
