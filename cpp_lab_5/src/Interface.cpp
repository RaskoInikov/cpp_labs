#include "../template/Interface.h"
#include <iostream>

Interface::Interface()
    : active_type(ClockType::NONE)
{
    smart_tree.set_compare_func([](const SmartClock &a, const SmartClock &b)
                                { return Interface::cmp_by_brand<SmartClock>(a, b); });
    wall_tree.set_compare_func([](const WallClock &a, const WallClock &b)
                               { return Interface::cmp_by_brand<WallClock>(a, b); });
    wrist_tree.set_compare_func([](const WristClock &a, const WristClock &b)
                                { return Interface::cmp_by_brand<WristClock>(a, b); });
}

Interface::~Interface()
{
}

void Interface::menu()
{
    while (true)
    {
        std::cout << "\n=== Main menu ===\n";
        std::cout << "1) SmartClock\n2) WallClock\n3) WristClock\n0) Exit\nChoice: ";

        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
            configure_sorting_for_tree<SmartClock>(smart_tree);
            tree_menu<SmartClock>(smart_tree, "SmartClock");
            break;
        case 2:
            configure_sorting_for_tree<WallClock>(wall_tree);
            tree_menu<WallClock>(wall_tree, "WallClock");
            break;
        case 3:
            configure_sorting_for_tree<WristClock>(wrist_tree);
            tree_menu<WristClock>(wrist_tree, "WristClock");
            break;
        default:
            std::cout << "Unknown option.\n";
        }
    }
}
