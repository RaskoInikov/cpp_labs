#pragma once
#include <stack>

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(std::function<bool(const T &, const T &)> comparator)
    : root(nullptr), cmp(comparator) {}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    clear();
}

template <class T>
void BinarySearchTree<T>::setComparator(std::function<bool(const T &, const T &)> comparator)
{
    cmp = comparator;
}

template <class T>
typename BinarySearchTree<T>::Node *
BinarySearchTree<T>::findMin(Node *node) const
{
    while (node && node->left)
        node = node->left;
    return node;
}

template <class T>
typename BinarySearchTree<T>::Node *
BinarySearchTree<T>::insertNode(Node *node, Node *parent, const T &value)
{
    if (!node)
    {
        Node *n = new Node(value);
        n->parent = parent;
        return n;
    }

    if (cmp(value, node->data))
        node->left = insertNode(node->left, node, value);
    else
        node->right = insertNode(node->right, node, value);

    return node;
}

template <class T>
void BinarySearchTree<T>::add(const T &value)
{
    root = insertNode(root, nullptr, value);
}

template <class T>
typename BinarySearchTree<T>::Node *
BinarySearchTree<T>::removeNode(Node *node, const T &value)
{
    if (!node)
        return nullptr;

    if (cmp(value, node->data))
        node->left = removeNode(node->left, value);
    else if (cmp(node->data, value))
        node->right = removeNode(node->right, value);
    else
    {
        if (!node->left)
        {
            Node *r = node->right;
            delete node;
            return r;
        }
        if (!node->right)
        {
            Node *l = node->left;
            delete node;
            return l;
        }

        Node *succ = findMin(node->right);
        node->data = succ->data;
        node->right = removeNode(node->right, succ->data);
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
void BinarySearchTree<T>::print() const
{
    if (!root)
    {
        std::cout << "(tree empty)\n";
        return;
    }

    inorderVisit([](const T &x)
                 { std::cout << x << "\n"; });
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
std::list<T> BinarySearchTree<T>::toList() const
{
    std::list<T> lst;
    inorderVisit([&](const T &x)
                 { lst.push_back(x); });
    return lst;
}

template <class T>
std::list<T> BinarySearchTree<T>::search(std::function<bool(const T &)> predicate) const
{
    std::list<T> res;
    inorderVisit([&](const T &x)
                 {
                     if (predicate(x))
                         res.push_back(x); });
    return res;
}
