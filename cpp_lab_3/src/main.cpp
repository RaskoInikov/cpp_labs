#include <iostream>
#include "../headers/WristClock.h"
#include "../headers/SmartClock.h"
#include "../headers/WallClock.h"

/*
  Demonstration in English as requested.

  The program will demonstrate:
  - input and output (operator>> / operator<<) for WristClock and SmartClock (these combine many parent fields),
  - copy-construction and assignment,
  - getters and setters usage.

  You will be prompted to enter several lines. Use plain text lines for String fields (brand, model, ...).
  For integer fields, enter a number on its own line (e.g. 2020).
*/

int main()
{
    std::cout << "Demo: create a WristClock (mechanical, inherits Clock->MechanicalClock->WristClock)\n";
    WristClock wc;
    std::cin >> wc; // reads Brand, Model, Year, Winding interval, Strap length
    std::cout << "\nYou entered WristClock:\n";
    std::cout << wc << std::endl;

    // copy construct
    WristClock wcCopy(wc);
    std::cout << "Copy-constructed WristClock:\n"
              << wcCopy << std::endl;

    // modify via setters and demonstrate getters
    wcCopy.setStrapLength(wcCopy.getStrapLength() + 5);
    std::cout << "After increasing strap length by 5 mm:\n"
              << wcCopy << std::endl;

    std::cout << "\nDemo: create a SmartClock (electronic -> smart)\n";
    SmartClock sc;
    std::cin >> sc; // reads Brand, Model, Year, Battery life, OS version
    std::cout << "\nYou entered SmartClock:\n";
    std::cout << sc << std::endl;

    // assignment
    SmartClock scAssigned;
    scAssigned = sc;
    std::cout << "Assigned SmartClock (copy via operator=):\n"
              << scAssigned << std::endl;

    // small demonstration of setters/getters
    scAssigned.setOsVersion(String("v2.0"));
    std::cout << "After setting OS version to v2.0:\n"
              << scAssigned << std::endl;

    // Optionally demonstrate WallClock which shares MechanicalClock (uncomment if desired)
    // WallClock wall;
    // std::cin >> wall;
    // std::cout << wall << std::endl;

    return 0;
}
