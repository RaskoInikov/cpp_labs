#pragma once

template <class T>
void Iterator<T>::pushLeft(typename BinarySearchTree<T>::Node *node)
{
    while (node)
    {
        stackNodes.push(node);
        node = node->left;
    }
}

template <class T>
Iterator<T>::Iterator(typename BinarySearchTree<T>::Node *root)
{
    pushLeft(root);
    if (!stackNodes.empty())
    {
        current = stackNodes.top();
        stackNodes.pop();
    }
    else
    {
        current = nullptr;
    }
}

template <class T>
Iterator<T> &Iterator<T>::operator++()
{
    if (current && current->right)
        pushLeft(current->right);
    if (!stackNodes.empty())
    {
        current = stackNodes.top();
        stackNodes.pop();
    }
    else
    {
        current = nullptr;
    }
    return *this;
}

template <class T>
Iterator<T> &Iterator<T>::operator--()
{
    // простой вариант: не реализация обратного обхода, а можно расширить через parent
    return *this;
}

template <class T>
T &Iterator<T>::operator*() const
{
    return current->data;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator &other) const
{
    return current != other.current;
}

template <class T>
bool Iterator<T>::operator==(const Iterator &other) const
{
    return current == other.current;
}
