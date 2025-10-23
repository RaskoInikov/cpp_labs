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
  cout << "=== CLASS Clock ===" << endl;
  int size;
  cout << "Enter array size: ";
  cin >> size;
  clearInputBuffer();

  Clock *clocks = new Clock[size];
  cout << "\n--- Input data ---" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << "Clock " << i + 1 << ":" << endl;
    cin >> clocks[i];
  }

  cout << "\n--- Clock Table ---" << endl;
  clocks[0].displayHeader();
  for (int i = 0; i < size; i++)
    cout << clocks[i] << endl;

  cout << "\n=== CLASS ElectronicClock ===" << endl;
  cout << "Enter array size: ";
  cin >> size;
  clearInputBuffer();

  ElectronicClock *electronic = new ElectronicClock[size];
  cout << "\n--- Input data ---" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << "ElectronicClock " << i + 1 << ":" << endl;
    cin >> electronic[i];
  }

  cout << "\n--- ElectronicClock Table ---" << endl;
  electronic[0].displayHeader();
  for (int i = 0; i < size; i++)
    cout << electronic[i] << endl;

  WallClock *wallClocks = new WallClock[size];
  cout << "\n--- Input data for WallClocks ---" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << "WallClock " << i + 1 << ":" << endl;
    cin >> wallClocks[i];
  }

  cout << "\n--- WallClock Table ---" << endl;
  wallClocks[0].displayHeader();
  for (int i = 0; i < size; i++)
    cout << wallClocks[i] << endl;

  cout << "\n=== CLASS MechanicalClock (WristClock) ===" << endl;
  cout << "Enter array size for WristClocks: ";
  cin >> size;
  clearInputBuffer();

  WristClock *wristClocks = new WristClock[size];
  cout << "\n--- Input data for WristClocks ---" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << "WristClock " << i + 1 << ":" << endl;
    cin >> wristClocks[i];
  }

  cout << "\n--- WristClock Table ---" << endl;
  wristClocks[0].displayHeader();
  for (int i = 0; i < size; i++)
    cout << wristClocks[i] << endl;

  cout << "\n=== Demonstration: SmartClock Editing ===" << endl;
  SmartClock smart(String("Apple"), String("Watch 9"), 2024, 18, String("watchOS 11"));

  int choice = -1;
  while (choice != 0)
  {
    cout << "\n--- SmartClock Menu ---" << endl;
    cout << "1. Change Brand" << endl;
    cout << "2. Change Model" << endl;
    cout << "3. Change Year" << endl;
    cout << "4. Change Battery Life" << endl;
    cout << "5. Change OS Version" << endl;
    cout << "0. Exit editing" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    clearInputBuffer();

    if (choice == 0)
      break;

    String s;
    int val;

    switch (choice)
    {
    case 1:
      cout << "Enter new brand: ";
      cin >> s;
      smart.setBrand(s);
      break;
    case 2:
      cout << "Enter new model: ";
      cin >> s;
      smart.setModel(s);
      break;
    case 3:
      cout << "Enter new year: ";
      cin >> val;
      smart.setYear(val);
      break;
    case 4:
      cout << "Enter new battery life (hours): ";
      cin >> val;
      smart.setBatteryLife(val);
      break;
    case 5:
      cout << "Enter new OS version: ";
      cin >> s;
      smart.setOsVersion(s);
      break;
    default:
      cout << "Invalid choice." << endl;
    }

    cout << "\nUpdated SmartClock:" << endl;
    smart.displayHeader();
    cout << smart << endl;
  }

  delete[] clocks;
  delete[] electronic;

  cout << "\nProgram terminated." << endl;
  return 0;
}