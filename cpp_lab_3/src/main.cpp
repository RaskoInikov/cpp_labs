#include <iostream>
#include <iomanip>
#include "../headers/Clock.h"
#include "../headers/ElectronicClock.h"
#include "../headers/MechanicalClock.h"
#include "../headers/SmartClock.h"
#include "../headers/WallClock.h"
#include "../headers/WristClock.h"
#include "../utils/string_utils.h"

using namespace std;

int main()
{
  int mainChoice;

  do
  {
    cout << "\n=== CLOCK SYSTEM ===" << endl;
    cout << "Choose clock type to fill:" << endl;
    cout << "1. WristClock" << endl;
    cout << "2. SmartClock" << endl;
    cout << "0. Exit program" << endl;
    cout << "Enter choice: ";
    cin >> mainChoice;
    clearInputBuffer();

    if (mainChoice == 0)
    {
      cout << "Exiting program..." << endl;
      break;
    }

    if (mainChoice != 1 && mainChoice != 2)
    {
      cout << "Invalid choice. Please try again." << endl;
      continue;
    }

    int size;
    cout << "Enter array size: ";
    cin >> size;
    clearInputBuffer();

    if (mainChoice == 1)
    {
      WristClock *wristClocks = new WristClock[size];

      cout << "\n--- Input data for WristClocks ---" << endl;
      for (int i = 0; i < size; i++)
      {
        cout << "\nWristClock " << i + 1 << ":" << endl;
        cin >> wristClocks[i];
      }

      cout << "\n--- WristClock Table ---" << endl;
      wristClocks[0].displayHeader();
      for (int i = 0; i < size; i++)
        cout << wristClocks[i] << endl;

      cout << "\nWould you like to edit any WristClock? (y/n): ";
      char ans;
      cin >> ans;
      clearInputBuffer();

      if (ans == 'y' || ans == 'Y')
      {
        int index;
        cout << "Enter index (1 - " << size << "): ";
        cin >> index;
        clearInputBuffer();

        if (index >= 1 && index <= size)
        {
          wristClocks[index - 1].edit();
          cout << "\nUpdated WristClock:\n";
          wristClocks[index - 1].displayHeader();
          cout << wristClocks[index - 1] << endl;
        }
        else
        {
          cout << "Invalid index." << endl;
        }
      }

      delete[] wristClocks;
    }

    else if (mainChoice == 2)
    {
      SmartClock *smartClocks = new SmartClock[size];

      cout << "\n--- Input data for SmartClocks ---" << endl;
      for (int i = 0; i < size; i++)
      {
        cout << "\nSmartClock " << i + 1 << ":" << endl;
        cin >> smartClocks[i];
      }

      cout << "\n--- SmartClock Table ---" << endl;
      smartClocks[0].displayHeader();
      for (int i = 0; i < size; i++)
        cout << smartClocks[i] << endl;

      cout << "\nWould you like to edit any SmartClock? (y/n): ";
      char ans;
      cin >> ans;
      clearInputBuffer();

      if (ans == 'y' || ans == 'Y')
      {
        int index;
        cout << "Enter index (1 - " << size << "): ";
        cin >> index;
        clearInputBuffer();

        if (index >= 1 && index <= size)
        {
          smartClocks[index - 1].edit();
          cout << "\nUpdated SmartClock:\n";
          smartClocks[index - 1].displayHeader();
          cout << smartClocks[index - 1] << endl;
        }
        else
        {
          cout << "Invalid index." << endl;
        }
      }

      delete[] smartClocks;
    }

  } while (true);

  cout << "\nProgram terminated." << endl;
  return 0;
}