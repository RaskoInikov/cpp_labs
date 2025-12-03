#pragma once
#ifndef TREE_TEMPLATE_H
#define TREE_TEMPLATE_H

#include "Node.h"
#include <iostream>

// Binary Search Tree (BST) template.
// compare_func: возвращает -1 (a < b), 0 (a == b), 1 (a > b).
// compare_func устанавливается динамически (через Interface).

template <typename T>
class TreeTemplate
{
private:
    Node<T> *root;
    int (*compare_func)(const T &a, const T &b);

protected:
    Node<T> *insert_rec(Node<T> *node, T *data);
    Node<T> *delete_rec(Node<T> *node, const T &key, bool &deleted);
    Node<T> *min_node(Node<T> *node) const;
    void inorder_rec(Node<T> *node) const;
    void clear_rec(Node<T> *node);
    Node<T> *search_by_key_rec(Node<T> *node, const T &key) const;

public:
    TreeTemplate();
    explicit TreeTemplate(int (*cmp)(const T &, const T &));
    ~TreeTemplate();

    Node<T> *get_root() const;

    void set_compare_func(int (*cmp)(const T &, const T &));
    int (*get_compare_func())(const T &, const T &);

    Node<T> *Insert(T *data);
    bool Delete(const T &key);
    Node<T> *Search(const T &key) const;
    void Inorder() const;
    void clear();
    bool empty() const;
};

#include "TreeTemplate.tpp"

#endif // TREE_TEMPLATE_H
