#pragma once
#ifndef INTERFACE_TPP
#define INTERFACE_TPP

#include <sstream>
#include <functional>

inline void Interface::clearInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline std::string Interface::readLineAllowEmpty()
{
    std::string s;
    std::getline(std::cin, s);
    return s;
}

template <typename U>
int Interface::cmp_by_brand(const U &a, const U &b)
{
    std::ostringstream sa, sb;
    sa << a.getBrand();
    sb << b.getBrand();
    int r = sa.str().compare(sb.str());
    if (r < 0)
        return -1;
    if (r > 0)
        return 1;
    return 0;
}

template <typename U>
int Interface::cmp_by_model(const U &a, const U &b)
{
    std::ostringstream sa, sb;
    sa << a.getModel();
    sb << b.getModel();
    int r = sa.str().compare(sb.str());
    if (r < 0)
        return -1;
    if (r > 0)
        return 1;
    return 0;
}

template <typename U>
int Interface::cmp_by_year(const U &a, const U &b)
{
    if (a.getYear() < b.getYear())
        return -1;
    if (a.getYear() > b.getYear())
        return 1;
    return 0;
}

template <typename U>
void Interface::configure_sorting_for_tree(TreeTemplate<U> &tree)
{
    std::cout << "Sort by:\n"
              << "1) Brand\n"
              << "2) Model\n"
              << "3) Year\n"
              << "Choice: ";

    int ch = 1;
    if (!(std::cin >> ch))
    {
        std::cin.clear();
        clearInputBuffer();
        ch = 1;
    }
    clearInputBuffer();

    if (ch == 1)
        tree.set_compare_func([this](const U &x, const U &y)
                              { return cmp_by_brand<U>(x, y); });
    else if (ch == 2)
        tree.set_compare_func([this](const U &x, const U &y)
                              { return cmp_by_model<U>(x, y); });
    else if (ch == 3)
        tree.set_compare_func([this](const U &x, const U &y)
                              { return cmp_by_year<U>(x, y); });
    else
        tree.set_compare_func([this](const U &x, const U &y)
                              { return cmp_by_brand<U>(x, y); });

    std::cout << "Comparator updated.\n";
}

template <typename U>
void Interface::tree_menu(TreeTemplate<U> &tree, const char *type_name)
{
    while (true)
    {
        std::cout << "\n--- " << type_name << " tree menu ---\n"
                  << "1 - Add element\n"
                  << "2 - Delete element\n"
                  << "3 - Search\n"
                  << "4 - Print tree\n"
                  << "5 - Configure sorting\n"
                  << "6 - Clear tree\n"
                  << "0 - Back\n"
                  << "Choice: ";

        int cmd = -1;
        if (!(std::cin >> cmd))
        {
            std::cin.clear();
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (cmd == 0)
            break;

        if (cmd == 1)
        {
            U *obj = new U();
            std::cin >> *obj;
            tree.Insert(obj);
            std::cout << "Element added.\n";
        }
        else if (cmd == 2)
        {
            U temp;
            std::cin >> temp;
            bool ok = tree.Delete(temp);
            std::cout << (ok ? "Deleted.\n" : "Not found.\n");
        }
        else if (cmd == 3)
        {
            search_by_fields<U>(tree);
        }
        else if (cmd == 4)
        {
            U tmp;
            tmp.displayHeader();
            std::cout << "\n";
            tree.Inorder();
            std::cout << "\n";
        }
        else if (cmd == 5)
        {
            configure_sorting_for_tree<U>(tree);
        }
        else if (cmd == 6)
        {
            tree.clear();
            std::cout << "Tree cleared.\n";
        }
        else
        {
            std::cout << "Unknown command.\n";
        }
    }
}

template <typename U>
void Interface::search_by_fields(TreeTemplate<U> &tree)
{
    if (tree.empty())
    {
        std::cout << "Tree empty.\n";
        return;
    }

    std::cout << "Brand (Enter to skip): ";
    std::string brand_line = readLineAllowEmpty();

    std::cout << "Model (Enter to skip): ";
    std::string model_line = readLineAllowEmpty();

    std::cout << "Year (Enter to skip, 0 to skip): ";
    std::string year_line = readLineAllowEmpty();

    bool use_brand = !brand_line.empty();
    bool use_model = !model_line.empty();
    bool use_year = false;
    int year_val = 0;
    if (!year_line.empty())
    {
        year_val = std::atoi(year_line.c_str());
        if (year_val != 0)
            use_year = true;
    }

    String sb, sm;
    if (use_brand)
        sb = String(brand_line.c_str());
    if (use_model)
        sm = String(model_line.c_str());

    U tmp;
    tmp.displayHeader();
    std::cout << "\n";

    std::function<void(Node<U> *)> visit = [&](Node<U> *node)
    {
        if (!node)
            return;
        visit(node->get_left());

        U *obj = node->get_data();
        if (obj)
        {
            bool match = true;
            if (use_brand && !(obj->getBrand() == sb))
                match = false;
            if (use_model && match && !(obj->getModel() == sm))
                match = false;
            if (use_year && match && !(obj->getYear() == year_val))
                match = false;
            if (match)
                std::cout << *obj << "\n";
        }

        visit(node->get_right());
    };

    visit(tree.get_root());
    std::cout << "\n";
}

#endif
