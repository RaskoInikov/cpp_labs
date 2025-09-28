#include "array.h"
#include <iostream>

void print_menu() {
    std::cout << "=~=~=~= OPTIONS =~=~=~=" << std::endl;
    std::cout << "1. Fill first array" << std::endl;
    std::cout << "2. Fill second array" << std::endl;
    std::cout << "3. Get intersection" << std::endl;
    std::cout << "4. Get union" << std::endl;
    std::cout << "5. Print first array" << std::endl;
    std::cout << "6. Print second array" << std::endl;
    std::cout << "7. Sort first array" << std::endl;
    std::cout << "8. Sort second array" << std::endl;
    std::cout << "0. EXIT" << std::endl << std::endl;
}

int main() {
    int option = 1;

    Array arr1;
    Array arr2;

    while (option != 0) {
        print_menu();
        std::cout << "OPTION:\t";
        std::cin >> option;

        switch (option) {
        case 1: {
            int length1;
            std::cout << "Enter length:\t";
            std::cin >> length1;

            arr1 = Array(length1);
            std::cout << "Enter " << length1 << " elements of array:\t";
            std::cin >> arr1;
            break;
        }
        case 2: {
            int length2;
            std::cout << "Enter length:\t";
            std::cin >> length2;

            arr2 = Array(length2);
            std::cout << "Enter " << length2 << " elements of array:\t";
            std::cin >> arr2;
            break;
        }
        case 3: {
            if (arr1.isEmpty() || arr2.isEmpty()) {
                std::cout << "One of arrays is empty" << std::endl;
                break;
            }
            Array intersection_arr = arr1.get_intersection(arr2);
            std::cout << std::endl << "Intersection:\t";
            std::cout << intersection_arr << std::endl;
            break;
        }
        case 4: {
            if (arr1.isEmpty() || arr2.isEmpty()) {
                std::cout << "One of arrays is empty" << std::endl;
                break;
            }
            Array union_arr = arr1.get_union(arr2);
            std::cout << std::endl << "Union:\t";
            std::cout << union_arr << std::endl;
            break;
        }
        case 5: {
            if (arr1.isEmpty()) {
                std::cout << std::endl << "Empty array!" << std::endl;
            } else {
                std::cout << std::endl << "Array:\t";
                std::cout << arr1 << std::endl;
            }
            break;
        }
        case 6: {
            if (arr2.isEmpty()) {
                std::cout << std::endl << "Empty array!" << std::endl;
            } else {
                std::cout << std::endl << "Array:\t";
                std::cout << arr2 << std::endl;
            }
            break;
        }
        case 7: {
            if (arr1.isEmpty()) {
                std::cout << "First array is empty" << std::endl;
                break;
            }
            arr1.sort();
            std::cout << "First array sorted!" << std::endl;
            break;
        }
        case 8: {
            if (arr2.isEmpty()) {
                std::cout << "Second array is empty" << std::endl;
                break;
            }
            arr2.sort();
            std::cout << "Second array sorted!" << std::endl;
            break;
        }
        case 0: {
            std::cout << "Bye!" << std::endl;
            break;
        }
        default:
            std::cout << "Wrong option!" << std::endl;
            break;
        }

        std::cout << std::endl;
    }
}
