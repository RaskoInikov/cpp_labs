#include <iostream>
#include "array.h"

int main()
{
    int choice = 1;
    Array arr1;
    Array arr2;

    do
    {
        std::cout << "\n+------------------------+\n";
        std::cout << "|          MENU          |\n";
        std::cout << "+------------------------+\n";
        std::cout << "| 1. Create arrays       |\n";
        std::cout << "| 2. Find intersection   |\n";
        std::cout << "| 3. Find union          |\n";
        std::cout << "| 4. Display arrays      |\n";
        std::cout << "| 5. Exit                |\n";
        std::cout << "+------------------------+\n";
        std::cout << "| Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int size1, size2;

            std::cout << "Enter size of first array: ";
            std::cin >> size1;
            arr1 = Array(size1);
            if (!arr1.is_empty())
            {
                std::cout << "Enter elements for first array:\n";
                arr1.input();
            }

            std::cout << "Enter size of second array: ";
            std::cin >> size2;
            arr2 = Array(size2);
            if (!arr2.is_empty())
            {
                std::cout << "Enter elements for second array:\n";
                arr2.input();
            }

            std::cout << "Arrays created successfully!\n";
            break;
        }
        case 2:
        {
            if (arr1.is_empty() || arr2.is_empty())
            {
                std::cout << "Please create arrays first!\n";
            }
            else
            {
                Array result = arr1.intersection(arr2);
                std::cout << "Intersection: ";
                result.display();
            }
            break;
        }
        case 3:
        {
            if (arr1.is_empty() || arr2.is_empty())
            {
                std::cout << "Please create arrays first!\n";
            }
            else
            {
                Array result = arr1.unionArrays(arr2);
                std::cout << "Union: ";
                result.display();
            }
            break;
        }
        case 4:
        {
            if (arr1.is_empty() || arr2.is_empty())
            {
                std::cout << "Please create arrays first!\n";
            }
            else
            {
                std::cout << "First array: ";
                arr1.display();
                std::cout << "Second array: ";
                arr2.display();
            }
            break;
        }
        case 5:
        {
            std::cout << "Exiting program...\n";
            break;
        }
        default:
            std::cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}