#pragma once
#include <fstream>
#include <stdexcept>
#include "../template/TreeTemplate.h"
#include "../template/Node.h"

template <typename T, typename Func>
void inorder_traverse(Node<T> *node, Func f)
{
    if (!node)
        return;
    inorder_traverse(node->get_left(), f);
    if (node->get_data())
        f(*node->get_data());
    inorder_traverse(node->get_right(), f);
}

template <typename T>
class FileTxt
{
    TreeTemplate<T> &tree;
    std::string filename;

public:
    FileTxt(const std::string &name, TreeTemplate<T> &t)
        : tree(t), filename(name) {}

    void save()
    {
        std::ofstream out(filename);
        if (!out)
            throw std::runtime_error("Text file open error");

        T header;
        header.displayHeader();
        out << "\n";

        inorder_traverse<T>(tree.get_root(), [&](const T &obj)
                            {
            obj.writeText(out);
            out << "\n"; });
    }

    void load()
    {
        std::ifstream in(filename);
        if (!in)
            throw std::runtime_error("Text file open error");

        tree.clear();

        while (in)
        {
            T *obj = new T();
            obj->readText(in);
            if (in)
                tree.Insert(obj);
            else
                delete obj;
        }
    }
};
