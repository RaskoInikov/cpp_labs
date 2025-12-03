#pragma once
#ifndef INTERFACE_TPP
#define INTERFACE_TPP

#include <sstream>

// ---- input helpers ----
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

// ---- generic comparators ----
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

// ---- configure sorting ----
template <typename U>
void Interface::configure_sorting_for_tree(TreeTemplate<U> &tree)
{
    std::cout << "Выберите поле для сортировки дерева:\n";
    std::cout << "1) Brand\n2) Model\n3) Year\nChoice: ";
    // read simple integer (no exceptions)
    int ch = 1;
    if (!(std::cin >> ch))
    {
        std::cin.clear();
        clearInputBuffer();
        ch = 1;
    }
    else
    {
        clearInputBuffer();
    }

    // Use captureless lambdas that convert to function pointers
    if (ch == 1)
    {
        tree.set_compare_func([](const U &x, const U &y) -> int
                              { return Interface::cmp_by_brand<U>(x, y); });
    }
    else if (ch == 2)
    {
        tree.set_compare_func([](const U &x, const U &y) -> int
                              { return Interface::cmp_by_model<U>(x, y); });
    }
    else if (ch == 3)
    {
        tree.set_compare_func([](const U &x, const U &y) -> int
                              { return Interface::cmp_by_year<U>(x, y); });
    }
    else
    {
        tree.set_compare_func([](const U &x, const U &y) -> int
                              { return Interface::cmp_by_brand<U>(x, y); });
    }

    std::cout << "Comparator set.\n";
}

// ---- tree_menu (шаблонная) ----
template <typename U>
void Interface::tree_menu(TreeTemplate<U> &tree, const char *type_name)
{
    while (true)
    {
        std::cout << "\n--- Working with " << type_name << " tree ---\n";
        std::cout << "1 - Add element\n2 - Delete element\n3 - Search by fields\n4 - Print tree\n5 - Configure sorting\n6 - Clear tree\n0 - Back\nChoice: ";

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
            // operator>> for clocks reads fields; ensure newline handled
            std::cin.clear();
            std::cin.sync();
            std::cin >> *obj;
            tree.Insert(obj);
            std::cout << "Added.\n";
        }
        else if (cmd == 2)
        {
            U temp;
            std::cin.clear();
            std::cin.sync();
            std::cin >> temp;
            bool ok = tree.Delete(temp);
            std::cout << (ok ? "Deleted element.\n" : "Element not found.\n");
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

// ---- search_by_fields (шаблонная) ----
template <typename U>
void Interface::search_by_fields(TreeTemplate<U> &tree)
{
    if (tree.empty())
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::cout << "Enter Brand to search (press Enter to skip): ";
    std::string brand_line = readLineAllowEmpty();

    std::cout << "Enter Model to search (press Enter to skip): ";
    std::string model_line = readLineAllowEmpty();

    std::cout << "Enter Year to search (press Enter to skip or 0 to skip): ";
    std::string year_line = readLineAllowEmpty();

    bool use_brand = !brand_line.empty();
    bool use_model = !model_line.empty();
    bool use_year = false;
    int year_val = 0;
    if (!year_line.empty())
    {
        // simple stoi without exceptions handling
        year_val = std::atoi(year_line.c_str());
        if (year_val != 0)
            use_year = true;
    }

    String searchBrand;
    String searchModel;
    if (use_brand)
        searchBrand = String(brand_line.c_str());
    if (use_model)
        searchModel = String(model_line.c_str());

    // Print header
    U tmp;
    tmp.displayHeader();
    std::cout << "\n";

    // traverse inorder and print matches
    // implement recursive struct
    struct Visitor
    {
        bool ub, um, uy;
        String sb, sm;
        int y;
        void visit(Node<U> *node)
        {
            if (!node)
                return;
            if (node->get_left())
                visit(node->get_left());
            U *obj = node->get_data();
            if (obj)
            {
                bool match = true;
                if (ub && !(obj->getBrand() == sb))
                    match = false;
                if (um && match && !(obj->getModel() == sm))
                    match = false;
                if (uy && match && !(obj->getYear() == y))
                    match = false;
                if (match)
                    std::cout << *obj;
            }
            if (node->get_right())
                visit(node->get_right());
        }
    };

    Visitor vis;
    vis.ub = use_brand;
    vis.um = use_model;
    vis.uy = use_year;
    vis.sb = searchBrand;
    vis.sm = searchModel;
    vis.y = year_val;

    vis.visit(tree.get_root());
    std::cout << "\n";
}

#endif // INTERFACE_TPP
