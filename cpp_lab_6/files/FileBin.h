#pragma once
#include <fstream>
#include <stdexcept>
#include "../template/TreeTemplate.h"
#include "../template/Node.h"

template <typename T, typename Func>
void inorder_traverse(Node<T> *node, Func f);

template <typename T>
class FileBin
{
    TreeTemplate<T> &tree;
    std::string filename;

public:
    FileBin(const std::string &name, TreeTemplate<T> &t)
        : tree(t), filename(name) {}

    void save()
    {
        std::ofstream out(filename, std::ios::binary);
        if (!out)
            throw std::runtime_error("Binary file open error");

        inorder_traverse<T>(tree.get_root(), [&](const T &obj)
                            { obj.writeBinary(out); });
    }

    void load()
    {
        std::ifstream in(filename, std::ios::binary);
        if (!in)
            throw std::runtime_error("Binary file open error");

        tree.clear();

        while (true)
        {
            T *obj = new T();
            if (!obj->readBinary(in))
            {
                delete obj;
                break;
            }
            tree.Insert(obj);
        }
    }
};
