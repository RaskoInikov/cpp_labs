#include "string.h"
#include <iostream>

using namespace std;

void displayMenu()
{
    cout << "\n=== String Class Test Menu ===" << endl;
    cout << "1. Test with custom string" << endl;
    cout << "2. Test all operators" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";
}

void testCustomString()
{
    cout << "\n=== Testing with Custom String ===" << endl;

    String custom;
    cout << "Enter your custom string: ";
    cin >> custom;

    cout << "=== Your string results ===" << endl;
    cout << "Your string: '" << custom << "'" << endl;
    cout << "Length: " << custom.len() << ", Capacity: " << custom.cap() << endl;

    String upper = custom;
    ++upper;
    cout << "Uppercase (++operator): '" << upper << "'" << endl;

    String lower = custom;
    lower++;
    cout << "Lowercase (operator++): '" << lower << "'" << endl;

    String trimmed = custom;
    --trimmed;
    cout << "Trimmed (--operator): '" << trimmed << "'" << endl;

    cout << "First 3 characters (operator()): '" << custom(0, 3) << "'" << endl;
    cout << "From position 2 to end (operator()): '" << custom(2, custom.len()) << "'" << endl;

    String test("test");
    cout << "Contains 'e': " << (custom.contains('e') ? "true" : "false") << endl;
    cout << "Contains \"test\": " << (custom.contains("test") ? "true" : "false") << endl;
    cout << "Contains String \"test\": " << (custom.contains(test) ? "true" : "false") << endl;
}

void testAllOperators()
{
    cout << "\n=== Testing All Operators ===" << endl;

    String s1("  hello");
    String s2("WORLD  ");

    cout << "=== Initial strings ===" << endl;
    cout << "s1: '" << s1 << "'" << endl;
    cout << "s2: '" << s2 << "'" << endl;

    cout << "\n=== Concatenation operators ===" << endl;
    String s3 = s1 + " " + s2;
    cout << "s1 + \" \" + s2: '" << s3 << "'" << endl;

    s1 += " there";
    cout << "s1 += \" there\": '" << s1 << "'" << endl;

    cout << "\n=== Comparison operators ===" << endl;
    cout << "s1 == s2: " << (s1 == s2 ? "true" : "false") << endl;
    cout << "s1 != s2: " << (s1 != s2 ? "true" : "false") << endl;
    cout << "s1 < s2: " << (s1 < s2 ? "true" : "false") << endl;
    cout << "s1 > s2: " << (s1 > s2 ? "true" : "false") << endl;
    cout << "s1 <= s2: " << (s1 <= s2 ? "true" : "false") << endl;
    cout << "s1 >= s2: " << (s1 >= s2 ? "true" : "false") << endl;

    cout << "\n=== Increment/decrement operators ===" << endl;
    ++s1;
    cout << "After ++s1 (uppercase): '" << s1 << "'" << endl;

    s2++;
    cout << "After s2++ (lowercase): '" << s2 << "'" << endl;

    --s1;
    cout << "After --s1 (trim): '" << s1 << "'" << endl;

    String s4 = s2--;
    cout << "After s2-- (trim and return copy):" << endl;
    cout << "s2: '" << s2 << "'" << endl;
    cout << "Returned copy: '" << s4 << "'" << endl;

    cout << "\n=== Index and substring operators ===" << endl;
    cout << "s3[0]: '" << s3[0] << "', s3[5]: '" << s3[5] << "'" << endl;

    String substr1 = s3(0, 5);
    cout << "s3(0, 5): '" << substr1 << "'" << endl;

    String substr2 = s3(3, 8);
    cout << "s3(3, 8): '" << substr2 << "'" << endl;

    cout << "\n=== Contains methods ===" << endl;
    cout << "s3 contains 'o': " << (s3.contains('o') ? "true" : "false") << endl;
    cout << "s3 contains \"world\": " << (s3.contains("world") ? "true" : "false") << endl;

    String search("hello");
    cout << "s3 contains String \"hello\": " << (s3.contains(search) ? "true" : "false") << endl;

    cout << "\n=== Assignment and copy ===" << endl;
    String s5 = s3;
    cout << "String s5 = s3: '" << s5 << "'" << endl;

    s5.clear();
    cout << "After s5.clear(): '" << s5 << "'" << endl;
}

int main()
{
    while (true)
    {
        displayMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            testCustomString();
            break;
        case 2:
            testAllOperators();
            break;
        case 0:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid option! Please try again." << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }

    return 0;
}