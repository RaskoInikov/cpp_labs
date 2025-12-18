#pragma once
#include "BinarySearchTree.h"

template <class T>
TreeIterator<T> &TreeIterator<T>::operator++()
{
    if (!tree)
    {
        current = nullptr;
        return *this;
    }
    if (!current)
    {
        return *this;
    }
    if (current->right)
    {
        Node *n = current->right;
        while (n->left)
            n = n->left;
        current = n;
    }
    else
    {
        Node *p = current->parent;
        while (p && current == p->right)
        {
            current = p;
            p = p->parent;
        }
        current = p;
    }
    return *this;
}

template <class T>
TreeIterator<T> &TreeIterator<T>::operator--()
{
    if (!tree)
    {
        current = nullptr;
        return *this;
    }
    if (!current)
    {
        current = tree->findMax(tree->root);
        return *this;
    }
    if (current->left)
    {
        Node *n = current->left;
        while (n->right)
            n = n->right;
        current = n;
    }
    else
    {
        Node *p = current->parent;
        while (p && current == p->left)
        {
            current = p;
            p = p->parent;
        }
        current = p;
    }
    return *this;
}
