#include <iostream>

// include headers (they include your String via relative path)
#include "../headers/Clock.h"
#include "../headers/MechanicalClock.h"
#include "../headers/ElectronicClock.h"
#include "../headers/WristClock.h"
#include "../headers/WallClock.h"
#include "../headers/SmartClock.h"

int main()
{
    // All comments and interactions in English as requested.

    std::cout << "=== Demo: Clock class hierarchy ===\n\n";

    // 1) Base Clock
    // Clock base;
    // std::cout << "Input base Clock data:\n";
    // std::cin >> base;
    // std::cout << "\nBase Clock data:\n"
    //           << base << std::endl;
    // base.start();

    // 2) MechanicalClock
    MechanicalClock mech;
    std::cout << "\nInput MechanicalClock data:\n";
    std::cin >> mech;
    std::cout << "\nMechanicalClock data:\n"
              << mech << std::endl;
    // mech.start();

    // // 3) ElectronicClock
    // ElectronicClock elec;
    // std::cout << "\nInput ElectronicClock data:\n";
    // std::cin >> elec;
    // std::cout << "\nElectronicClock data:\n"
    //           << elec << std::endl;
    // elec.start();
    // elec.addFirmwareNote(String("v1.0 release notes"));

    // // 4) WristClock (child of MechanicalClock)
    // WristClock wrist(String("Omega"), String("Speedy"), 2020, String("Manual"), 48, String("Leather"));
    // std::cout << "\nWristClock initial:\n"
    //           << wrist << std::endl;
    // wrist.wear();
    // wrist.addMaintenanceRecord(String("Polished case"));

    // // 5) WallClock (child of MechanicalClock)
    // WallClock wall(String("Seiko"), String("WallMaster"), 2018, String("Pendulum"), 0, 300);
    // std::cout << "\nWallClock initial:\n"
    //           << wall << std::endl;
    // wall.hangOnWall();

    // // 6) SmartClock (child of ElectronicClock)
    // SmartClock smart(String("FitTime"), String("X100"), 2022, String("OLED"), 72);
    // std::cout << "\nSmartClock initial:\n"
    //           << smart << std::endl;
    // smart.installApp(String("Weather"));
    // smart.installApp(String("Music"));
    // std::cout << "\nSmartClock after installing apps:\n"
    //           << smart << std::endl;

    // // Demonstrate copy constructors
    // WristClock wristCopy = wrist;
    // std::cout << "\nCopied WristClock:\n"
    //           << wristCopy << std::endl;

    // SmartClock smartCopy = smart;
    // std::cout << "\nCopied SmartClock:\n"
    //           << smartCopy << std::endl;

    std::cout << "\n=== End of demo ===\n";
    return 0;
}
