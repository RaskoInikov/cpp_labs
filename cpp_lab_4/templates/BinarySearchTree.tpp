#pragma once
#include "TreeIterator.h"
#include <algorithm>
#include <stack>
#include <stdexcept>

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr), cmp(nullptr) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(std::function<bool(const T &, const T &)> comparator)
    : root(nullptr), cmp(comparator) {}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() { clear(); }

template <class T>
void BinarySearchTree<T>::setComparator(std::function<bool(const T &, const T &)> comparator)
{
    cmp = comparator;
}

template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::findMin(Node *node) const
{
    if (!node)
        return nullptr;
    while (node->left)
        node = node->left;
    return node;
}

template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::findMax(Node *node) const
{
    if (!node)
        return nullptr;
    while (node->right)
        node = node->right;
    return node;
}

template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::insertNode(Node *node, Node *parent, const T &value)
{
    if (!cmp)
        throw std::runtime_error("BinarySearchTree: comparator not set");
    if (!node)
    {
        Node *n = new Node(value);
        n->parent = parent;
        return n;
    }
    if (cmp(value, node->data))
    {
        node->left = insertNode(node->left, node, value);
    }
    else
    {
        node->right = insertNode(node->right, node, value);
    }
    return node;
}

template <class T>
void BinarySearchTree<T>::add(const T &value)
{
    root = insertNode(root, nullptr, value);
}

template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::removeNode(Node *node, const T &value)
{
    if (!node)
        return nullptr;
    if (!cmp)
        throw std::runtime_error("BinarySearchTree: comparator not set");
    if (cmp(value, node->data))
    {
        node->left = removeNode(node->left, value);
    }
    else if (cmp(node->data, value))
    {
        node->right = removeNode(node->right, value);
    }
    else
    {
        if (!node->left)
        {
            Node *r = node->right;
            if (r)
                r->parent = node->parent;
            delete node;
            return r;
        }
        else if (!node->right)
        {
            Node *l = node->left;
            if (l)
                l->parent = node->parent;
            delete node;
            return l;
        }
        else
        {
            Node *succ = findMin(node->right);
            node->data = succ->data;
            node->right = removeNode(node->right, succ->data);
        }
    }
    return node;
}

template <class T>
void BinarySearchTree<T>::remove(const T &value)
{
    root = removeNode(root, value);
}

template <class T>
void BinarySearchTree<T>::clearNode(Node *node)
{
    if (!node)
        return;
    clearNode(node->left);
    clearNode(node->right);
    delete node;
}

template <class T>
void BinarySearchTree<T>::clear()
{
    clearNode(root);
    root = nullptr;
}

template <class T>
typename BinarySearchTree<T>::iterator BinarySearchTree<T>::begin() const
{
    return iterator(findMin(root), this);
}

template <class T>
typename BinarySearchTree<T>::iterator BinarySearchTree<T>::end() const
{
    return iterator(nullptr, this);
}

template <class T>
void BinarySearchTree<T>::print() const
{
    if (!root)
    {
        std::cout << "(tree is empty)\n";
        return;
    }
    T sample;
    sample.displayHeader();
    std::cout << "\n";
    printNode(root, "", true);
}

template <class T>
void BinarySearchTree<T>::printNode(Node *node, const std::string &prefix, bool isRoot) const
{
    if (!node)
        return;

    std::cout << prefix;

    if (isRoot)
        std::cout << "(root) ";
    else
        std::cout << (node == node->parent->left ? "L── " : "R── ");

    std::cout << node->data << "\n";
    std::string childPrefix = prefix + (isRoot ? "    " : (node == node->parent->left ? "│   " : "    "));

    if (node->left)
        printNode(node->left, childPrefix, false);

    if (node->right)
        printNode(node->right, childPrefix, false);
}

template <class T>
void BinarySearchTree<T>::printList() const
{
    if (!root)
    {
        std::cout << "(tree is empty)\n";
        return;
    }

    T sample;
    sample.displayHeader();
    std::cout << "\n";

    std::stack<Node *> st;
    st.push(root);

    while (!st.empty())
    {
        Node *node = st.top();
        st.pop();
        std::cout << node->data << "\n";
        if (node->right)
            st.push(node->right);
        if (node->left)
            st.push(node->left);
    }
}

template <class T>
void BinarySearchTree<T>::inorderVisit(std::function<void(const T &)> visitor) const
{
    std::stack<Node *> st;
    Node *cur = root;
    while (cur || !st.empty())
    {
        while (cur)
        {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top();
        st.pop();
        visitor(cur->data);
        cur = cur->right;
    }
}

template <class T>
std::vector<T> BinarySearchTree<T>::toVector() const
{
    std::vector<T> v;
    inorderVisit([&v](const T &x)
                 { v.push_back(x); });
    return v;
}

template <class T>
void BinarySearchTree<T>::buildFromVector(const std::vector<T> &v)
{
    clear();
    for (const T &x : v)
        add(x);
}

template <class T>
std::vector<T> BinarySearchTree<T>::search(std::function<bool(const T &)> predicate) const
{
    std::vector<T> result;
    inorderVisit([&](const T &x)
                 { if (predicate(x)) result.push_back(x); });
    return result;
}
