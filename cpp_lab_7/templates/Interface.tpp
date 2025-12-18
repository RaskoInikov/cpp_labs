#pragma once

/* ===== CONSTRUCTOR ===== */

template <typename T>
Interface<T>::Interface(const std::string &name_) : name(name_)
{
    auto fields = Reflection<T>::fields();
    std::list<int> ids;
    for (const auto &f : fields)
        ids.push_back(f.id);

    if (!fields.empty())
        tree.setComparator(makeComparator(fields, ids));
}

/* ===== UTILS ===== */

template <typename T>
void Interface<T>::clearStdin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
std::list<int> Interface<T>::parseFieldLine(const std::string &line)
{
    std::istringstream iss(line);
    std::list<int> ids;
    int x;
    while (iss >> x)
        ids.push_back(x);
    return ids;
}

/* ===== COMPARATOR ===== */

template <typename T>
std::function<bool(const T &, const T &)>
Interface<T>::makeComparator(const std::list<FD> &fields,
                             const std::list<int> &ids)
{
    return [fields, ids](const T &a, const T &b)
    {
        for (int id : ids)
        {
            auto it = std::find_if(fields.begin(), fields.end(),
                                   [&](const FD &f)
                                   { return f.id == id; });

            if (it == fields.end())
                continue;

            if (it->type == FieldType::STR)
            {
                if (it->getStr(a) < it->getStr(b))
                    return true;
                if (it->getStr(b) < it->getStr(a))
                    return false;
            }
            else
            {
                if (it->getInt(a) < it->getInt(b))
                    return true;
                if (it->getInt(b) < it->getInt(a))
                    return false;
            }
        }
        return false;
    };
}

/* ===== PREDICATE ===== */

template <typename T>
std::function<bool(const T &)>
Interface<T>::makePredicate(const std::list<FD> &fields,
                            const std::list<int> &ids,
                            const std::list<std::string> &values)
{
    return [fields, ids, values](const T &obj)
    {
        auto vit = values.begin();
        for (int id : ids)
        {
            auto it = std::find_if(fields.begin(), fields.end(),
                                   [&](const FD &f)
                                   { return f.id == id; });

            if (it == fields.end())
                continue;

            if (it->type == FieldType::STR)
            {
                if (std::string(it->getStr(obj).c_str()) != *vit)
                    return false;
            }
            else
            {
                if (it->getInt(obj) != std::stoi(*vit))
                    return false;
            }
            ++vit;
        }
        return true;
    };
}

/* ===== TREE OPS ===== */

template <typename T>
void Interface<T>::addInteractive()
{
    T obj;
    std::cin >> obj;
    tree.add(obj);
}

template <typename T>
void Interface<T>::removeInteractive()
{
    T obj;
    std::cin >> obj;
    tree.remove(obj);
}

template <typename T>
void Interface<T>::printTree() const
{
    T h;
    h.displayHeader();
    std::cout << "\n";
    tree.print();
}

/* ===== LIST OPS ===== */

template <typename T>
void Interface<T>::buildListFromTree()
{
    lst = tree.toList();
    listBuilt = true;
    std::cout << "Tree unfolded into list\n";
}

template <typename T>
void Interface<T>::printList()
{
    if (!listBuilt)
    {
        std::cout << "List is empty. Build it first.\n";
        return;
    }

    T h;
    h.displayHeader();
    std::cout << "\n";

    Algorithms::print(lst.begin(), lst.end());
}

template <typename T>
void Interface<T>::sortList()
{
    if (!listBuilt)
    {
        std::cout << "List is empty. Build it first.\n";
        return;
    }

    auto fields = Reflection<T>::fields();
    std::cout << "Sort list by fields:\n";
    for (const auto &f : fields)
        std::cout << f.id << ") " << f.name << "\n";

    clearStdin();
    std::string line;
    std::getline(std::cin, line);
    auto ids = parseFieldLine(line);

    auto cmp = makeComparator(fields, ids);
    Algorithms::sortList(lst, cmp);

    std::cout << "List sorted\n";
}

template <typename T>
void Interface<T>::searchInList()
{
    if (!listBuilt)
    {
        std::cout << "List is empty. Build it first.\n";
        return;
    }

    auto fields = Reflection<T>::fields();
    std::cout << "Search in list by fields:\n";
    for (const auto &f : fields)
        std::cout << f.id << ") " << f.name << "\n";

    clearStdin();
    std::string line;
    std::getline(std::cin, line);
    auto ids = parseFieldLine(line);

    std::list<std::string> values;
    for (int id : ids)
    {
        auto it = std::find_if(fields.begin(), fields.end(),
                               [&](const FD &f)
                               { return f.id == id; });

        std::cout << "Value for " << it->name << ": ";
        std::string v;
        std::getline(std::cin, v);
        values.push_back(v);
    }

    auto pred = makePredicate(fields, ids, values);

    bool found = false;
    T h;
    h.displayHeader();
    std::cout << "\n";

    for (const auto &x : lst)
    {
        if (pred(x))
        {
            std::cout << x << "\n";
            found = true;
        }
    }

    if (!found)
        std::cout << "Nothing found\n";
}

/* ===== MENU ===== */

template <typename T>
void Interface<T>::runMenu()
{
    int c = -1;
    while (c != 0)
    {
        std::cout << "\n--- " << name << " MENU ---\n"
                  << "1 Add\n2 Remove\n3 Print tree\n"
                  << "4 Build list from tree\n"
                  << "5 Print list\n"
                  << "6 Sort list\n"
                  << "7 Search list\n"
                  << "0 Back\n> ";

        std::cin >> c;
        clearStdin();

        switch (c)
        {
        case 1:
            addInteractive();
            break;
        case 2:
            removeInteractive();
            break;
        case 3:
            printTree();
            break;
        case 4:
            buildListFromTree();
            break;
        case 5:
            printList();
            break;
        case 6:
            sortList();
            break;
        case 7:
            searchInList();
            break;
        }
    }
}
