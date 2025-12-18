#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <algorithm>
#include <iostream>

namespace Algorithms
{
    template <typename It>
    void print(It begin, It end)
    {
        for (It it = begin; it != end; ++it)
            std::cout << *it << "\n";
    }

    template <typename It, typename Pred>
    It findIf(It begin, It end, Pred p)
    {
        return std::find_if(begin, end, p);
    }

    template <typename T, typename Comp>
    void sortList(std::list<T> &lst, Comp cmp)
    {
        lst.sort(cmp);
    }
}

#endif
