#include "../headers/Clock.h"
#include "../headers/ElectronicClock.h"
#include "../headers/MechanicalClock.h"
#include "../headers/SmartClock.h"
#include "../headers/WallClock.h"
#include "../headers/WristClock.h"
#include "../utils/string_utils.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <memory>

int main()
{
  std::vector<ElectronicClock> electronicClocks;
  std::vector<MechanicalClock> mechanicalClocks;
  std::vector<SmartClock> smartClocks;
  std::vector<WallClock> wallClocks;
  std::vector<WristClock> wristClocks;

  while (true)
  {
    std::cout << "\n=== CLOCK MENU ===\n"
              << "1. Add ElectronicClock\n"
              << "2. Add MechanicalClock\n"
              << "3. Add SmartClock\n"
              << "4. Add WallClock\n"
              << "5. Add WristClock\n"
              << "6. Display ElectronicClocks\n"
              << "7. Display MechanicalClocks\n"
              << "8. Display SmartClocks\n"
              << "9. Display WallClocks\n"
              << "10. Display WristClocks\n"
              << "11. Edit Clock\n"
              << "0. Exit\n";

    int choice = -1;
    handleUserInput(choice);

    if (choice == 0)
      break;

    switch (choice)
    {
    case 1:
    {
      int n = -1;
      std::cout << "How many ElectronicClocks to add? ";
      handleUserInput(n);

      for (int i = 0; i < n; ++i)
      {
        ElectronicClock ec;
        std::cout << "\n--- ElectronicClock #" << (i + 1) << " ---\n";
        std::cin >> ec;
        electronicClocks.push_back(ec);
      }
      break;
    }

    case 2:
    {
      int n;
      std::cout << "How many MechanicalClocks to add? ";
      handleUserInput(n);

      for (int i = 0; i < n; ++i)
      {
        MechanicalClock mc;
        std::cout << "\n--- MechanicalClock #" << (i + 1) << " ---\n";
        std::cin >> mc;
        mechanicalClocks.push_back(mc);
      }
      break;
    }

    case 3:
    {
      int n;
      std::cout << "How many SmartClocks to add? ";
      handleUserInput(n);

      for (int i = 0; i < n; ++i)
      {
        SmartClock sc;
        std::cout << "\n--- SmartClock #" << (i + 1) << " ---\n";
        std::cin >> sc;
        smartClocks.push_back(sc);
      }
      break;
    }

    case 4:
    {
      int n;
      std::cout << "How many WallClocks to add? ";
      handleUserInput(n);

      for (int i = 0; i < n; ++i)
      {
        WallClock wc;
        std::cout << "\n--- WallClock #" << (i + 1) << " ---\n";
        std::cin >> wc;
        wallClocks.push_back(wc);
      }
      break;
    }

    case 5:
    {
      int n;
      std::cout << "How many WristClocks to add? ";
      handleUserInput(n);

      for (int i = 0; i < n; ++i)
      {
        WristClock wr;
        std::cout << "\n--- WristClock #" << (i + 1) << " ---\n";
        std::cin >> wr;
        wristClocks.push_back(wr);
      }
      break;
    }

      // === DISPLAY ===

    case 6:
    {
      if (electronicClocks.empty())
      {
        std::cout << "No ElectronicClocks.\n";
        break;
      }

      ElectronicClock ec;
      ec.displayHeader();
      std::cout << "\n"
                << std::string(54, '-') << "\n";
      for (const ElectronicClock &c : electronicClocks)
        std::cout << c << "\n";
      break;
    }

    case 7:
    {
      if (mechanicalClocks.empty())
      {
        std::cout << "No MechanicalClocks.\n";
        break;
      }

      MechanicalClock mc;
      mc.displayHeader();
      std::cout << "\n"
                << std::string(54, '-') << "\n";
      for (const MechanicalClock &c : mechanicalClocks)
        std::cout << c << "\n";
      break;
    }

    case 8:
    {
      if (smartClocks.empty())
      {
        std::cout << "No SmartClocks.\n";
        break;
      }

      SmartClock sc;
      sc.displayHeader();
      std::cout << "\n"
                << std::string(70, '-') << "\n";
      for (const SmartClock &c : smartClocks)
        std::cout << c << "\n";
      break;
    }

    case 9:
    {
      if (wallClocks.empty())
      {
        std::cout << "No WallClocks.\n";
        break;
      }

      WallClock wc;
      wc.displayHeader();
      std::cout << "\n"
                << std::string(70, '-') << "\n";
      for (const WallClock &c : wallClocks)
        std::cout << c << "\n";
      break;
    }

    case 10:
    {
      if (wristClocks.empty())
      {
        std::cout << "No WristClocks.\n";
        break;
      }

      WristClock wr;
      wr.displayHeader();
      std::cout << "\n"
                << std::string(70, '-') << "\n";
      for (const WristClock &c : wristClocks)
        std::cout << c << "\n";
      break;
    }

    // === EDIT ===
    case 11:
    {
      std::cout << "Select clock type to edit:\n"
                << "1. Electronic\n"
                << "2. Mechanical\n"
                << "3. Smart\n"
                << "4. Wall\n"
                << "5. Wrist\n"
                << "Choice: ";
      int t;
      std::cin >> t;

      size_t idx;
      switch (t)
      {
      case 1:
        if (electronicClocks.empty())
        {
          std::cout << "No ElectronicClocks.\n";
          break;
        }
        std::cout << "Enter index (0-" << electronicClocks.size() - 1 << "): ";
        std::cin >> idx;
        if (idx >= electronicClocks.size())
          std::cout << "Invalid index.\n";
        else
          electronicClocks[idx].edit();
        break;

      case 2:
        if (mechanicalClocks.empty())
        {
          std::cout << "No MechanicalClocks.\n";
          break;
        }
        std::cout << "Enter index (0-" << mechanicalClocks.size() - 1 << "): ";
        std::cin >> idx;
        if (idx >= mechanicalClocks.size())
          std::cout << "Invalid index.\n";
        else
          mechanicalClocks[idx].edit();
        break;

      case 3:
        if (smartClocks.empty())
        {
          std::cout << "No SmartClocks.\n";
          break;
        }
        std::cout << "Enter index (0-" << smartClocks.size() - 1 << "): ";
        std::cin >> idx;
        if (idx >= smartClocks.size())
          std::cout << "Invalid index.\n";
        else
          smartClocks[idx].edit();
        break;

      case 4:
        if (wallClocks.empty())
        {
          std::cout << "No WallClocks.\n";
          break;
        }
        std::cout << "Enter index (0-" << wallClocks.size() - 1 << "): ";
        std::cin >> idx;
        if (idx >= wallClocks.size())
          std::cout << "Invalid index.\n";
        else
          wallClocks[idx].edit();
        break;

      case 5:
        if (wristClocks.empty())
        {
          std::cout << "No WristClocks.\n";
          break;
        }
        std::cout << "Enter index (0-" << wristClocks.size() - 1 << "): ";
        std::cin >> idx;
        if (idx >= wristClocks.size())
          std::cout << "Invalid index.\n";
        else
          wristClocks[idx].edit();
        break;

      default:
        std::cout << "Invalid type.\n";
      }
      break;
    }

    default:
      std::cout << "Invalid choice.\n";
    }
  }

  return 0;
}
