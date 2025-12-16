#pragma once
#ifndef TREE_TEMPLATE_H
#define TREE_TEMPLATE_H

#include "Node.h"
#include <iostream>
#include <functional>

template <typename T>
class TreeTemplate
{
private:
    Node<T> *root;
    std::function<int(const T &, const T &)> compare_func;

    Node<T> *insert_rec(Node<T> *node, T *data);
    Node<T> *delete_rec(Node<T> *node, const T &key, bool &deleted);
    Node<T> *min_node(Node<T> *node) const;
    void inorder_rec(Node<T> *node) const;
    void clear_rec(Node<T> *node);
    Node<T> *search_by_key_rec(Node<T> *node, const T &key) const;

public:
    TreeTemplate();
    explicit TreeTemplate(std::function<int(const T &, const T &)> cmp);
    ~TreeTemplate();

    Node<T> *get_root() const;

    void set_compare_func(std::function<int(const T &, const T &)> cmp);
    std::function<int(const T &, const T &)> get_compare_func() const;

    Node<T> *Insert(T *data);
    bool Delete(const T &key);
    Node<T> *Search(const T &key) const;
    void Inorder() const;
    void clear();
    bool empty() const;
};

#include "TreeTemplate.tpp"

#endif
