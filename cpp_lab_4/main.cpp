#include <iostream>
#include <memory>
#include <string>

#include "templates/Interface.h"
#include "templates/Reflection.h"

// include your clock headers
#include "headers/Clock.h"
#include "headers/ElectronicClock.h"
#include "headers/MechanicalClock.h"
#include "headers/SmartClock.h"
#include "headers/WallClock.h"
#include "headers/WristClock.h"

void clearStdin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    while (true)
    {
        std::cout << "\n--- Main Menu: Choose object type ---\n";
        std::cout << "1) ElectronicClock\n";
        std::cout << "2) MechanicalClock\n";
        std::cout << "3) SmartClock\n";
        std::cout << "4) WallClock\n";
        std::cout << "5) WristClock\n";
        std::cout << "0) Exit\n";
        std::cout << "Choice: ";
        int choice;
        if (!(std::cin >> choice))
        {
            clearStdin();
            std::cout << "Invalid input.\n";
            continue;
        }
        clearStdin();

        switch (choice)
        {
        case 1:
        {
            Interface<ElectronicClock> iface("ElectronicClock");
            iface.runMenu();
            break;
        }
        case 2:
        {
            Interface<MechanicalClock> iface("MechanicalClock");
            iface.runMenu();
            break;
        }
        case 3:
        {
            Interface<SmartClock> iface("SmartClock");
            iface.runMenu();
            break;
        }
        case 4:
        {
            Interface<WallClock> iface("WallClock");
            iface.runMenu();
            break;
        }
        case 5:
        {
            Interface<WristClock> iface("WristClock");
            iface.runMenu();
            break;
        }
        case 0:
            std::cout << "Goodbye!\n";
            return 0;
        default:
            std::cout << "Unknown selection.\n";
        }
    }
    return 0;
}
