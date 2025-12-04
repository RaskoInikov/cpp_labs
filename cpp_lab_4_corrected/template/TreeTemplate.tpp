#pragma once
#ifndef TREE_TEMPLATE_TPP
#define TREE_TEMPLATE_TPP

#include <sstream>

template <typename T>
static int default_compare_clock(const T &a, const T &b)
{
    std::ostringstream sa, sb;
    sa << a.getBrand();
    sb << b.getBrand();
    int r = sa.str().compare(sb.str());
    if (r < 0)
        return -1;
    if (r > 0)
        return 1;

    std::ostringstream ma, mb;
    ma << a.getModel();
    mb << b.getModel();
    r = ma.str().compare(mb.str());
    if (r < 0)
        return -1;
    if (r > 0)
        return 1;

    if (a.getYear() < b.getYear())
        return -1;
    if (a.getYear() > b.getYear())
        return 1;

    return 0;
}

template <typename T>
TreeTemplate<T>::TreeTemplate()
    : root(nullptr), compare_func(default_compare_clock<T>)
{
}

template <typename T>
TreeTemplate<T>::TreeTemplate(std::function<int(const T &, const T &)> cmp)
    : root(nullptr), compare_func(cmp ? cmp : default_compare_clock<T>)
{
}

template <typename T>
TreeTemplate<T>::~TreeTemplate()
{
    clear();
}

template <typename T>
Node<T> *TreeTemplate<T>::get_root() const
{
    return root;
}

template <typename T>
void TreeTemplate<T>::set_compare_func(std::function<int(const T &, const T &)> cmp)
{
    if (cmp)
        compare_func = cmp;
    else
        compare_func = default_compare_clock<T>;
}

template <typename T>
std::function<int(const T &, const T &)> TreeTemplate<T>::get_compare_func() const
{
    return compare_func;
}

template <typename T>
Node<T> *TreeTemplate<T>::min_node(Node<T> *node) const
{
    if (!node)
        return nullptr;
    Node<T> *cur = node;
    while (cur->get_left())
        cur = cur->get_left();
    return cur;
}

template <typename T>
Node<T> *TreeTemplate<T>::insert_rec(Node<T> *node, T *data)
{
    if (!data)
        return node;
    if (!node)
    {
        Node<T> *n = new Node<T>(data, nullptr, nullptr, nullptr);
        return n;
    }

    int cmp = compare_func(*data, *(node->get_data()));
    if (cmp < 0)
    {
        Node<T> *leftRes = insert_rec(node->get_left(), data);
        node->set_left(leftRes);
    }
    else
    {
        Node<T> *rightRes = insert_rec(node->get_right(), data);
        node->set_right(rightRes);
    }
    return node;
}

template <typename T>
Node<T> *TreeTemplate<T>::Insert(T *data)
{
    if (!data)
        return root;
    if (!root)
    {
        root = new Node<T>(data, nullptr, nullptr, nullptr);
        return root;
    }
    root = insert_rec(root, data);
    if (root)
        root->set_parent(nullptr);
    return root;
}

template <typename T>
Node<T> *TreeTemplate<T>::delete_rec(Node<T> *node, const T &key, bool &deleted)
{
    if (!node)
        return nullptr;

    int cmp = compare_func(key, *(node->get_data()));
    if (cmp < 0)
    {
        node->set_left(delete_rec(node->get_left(), key, deleted));
    }
    else if (cmp > 0)
    {
        node->set_right(delete_rec(node->get_right(), key, deleted));
    }
    else
    {
        deleted = true;

        if (!node->get_left() && !node->get_right())
        {
            if (node->get_data())
                delete node->get_data();
            delete node;
            return nullptr;
        }

        if (!node->get_left())
        {
            Node<T> *r = node->get_right();
            if (r)
                r->set_parent(node->get_parent());
            if (node->get_data())
                delete node->get_data();
            delete node;
            return r;
        }

        if (!node->get_right())
        {
            Node<T> *l = node->get_left();
            if (l)
                l->set_parent(node->get_parent());
            if (node->get_data())
                delete node->get_data();
            delete node;
            return l;
        }

        Node<T> *succ = min_node(node->get_right());
        if (succ && succ->get_data())
        {
            if (node->get_data())
                delete node->get_data();
            node->set_data(new T(*(succ->get_data())));
            node->set_right(delete_rec(node->get_right(), *(succ->get_data()), deleted));
        }
    }
    return node;
}

template <typename T>
bool TreeTemplate<T>::Delete(const T &key)
{
    bool deleted = false;
    root = delete_rec(root, key, deleted);
    if (root)
        root->set_parent(nullptr);
    return deleted;
}

template <typename T>
Node<T> *TreeTemplate<T>::search_by_key_rec(Node<T> *node, const T &key) const
{
    if (!node)
        return nullptr;
    int cmp = compare_func(key, *(node->get_data()));
    if (cmp == 0)
        return node;
    if (cmp < 0)
        return search_by_key_rec(node->get_left(), key);
    return search_by_key_rec(node->get_right(), key);
}

template <typename T>
Node<T> *TreeTemplate<T>::Search(const T &key) const
{
    return search_by_key_rec(root, key);
}

template <typename T>
void TreeTemplate<T>::inorder_rec(Node<T> *node) const
{
    if (!node)
        return;
    if (node->get_left())
        inorder_rec(node->get_left());
    if (node->get_data())
        std::cout << *(node->get_data()) << "\n";
    if (node->get_right())
        inorder_rec(node->get_right());
}

template <typename T>
void TreeTemplate<T>::Inorder() const
{
    inorder_rec(root);
}

template <typename T>
void TreeTemplate<T>::clear_rec(Node<T> *node)
{
    if (!node)
        return;
    if (node->get_left())
        clear_rec(node->get_left());
    if (node->get_right())
        clear_rec(node->get_right());
    if (node->get_data())
    {
        delete node->get_data();
    }
    delete node;
}

template <typename T>
void TreeTemplate<T>::clear()
{
    if (!root)
        return;
    clear_rec(root);
    root = nullptr;
}

template <typename T>
bool TreeTemplate<T>::empty() const
{
    return root == nullptr;
}

#endif
