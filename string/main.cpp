#include "string.h"
#include <iostream>
using namespace std;

int main()
{
    String a, b, c;
    cout << "Print string" << endl;
    cin >> a;
    cout << "Print string" << endl;
    cin >> b;
    cout << "Print string" << endl;
    cin >> c;

    // cout << (((((a + " " + b)(0, 5) += c)[1] == 'e') ? ++a : --b) <= c ? a : b) << endl;

    // cout <<
    // (++a) + b + c + a(0,2) + (b += a) << " " <<
    // ((a == b) ? a : b) << " " <<
    // ((a != c) ? b : c) << " " <<
    // ((a < b) ? a : b) << " " <<
    // ((a > c) ? a : c) << " " <<
    // ((a <= b) ? a : b) << " " <<
    // ((a >= c) ? a : c) << " " <<
    // a[0] << " " <<
    // a(1,3) << endl;

    // cout << ((((a += b) + c)(0, 5), ++a, --b, ((a == b) ? a : b), ((a != c) ? b : c), ((a < b) ? a : b), ((a > c) ? a : c), ((a <= b) ? a : b), ((a >= c) ? a : c), a[0], a(1, 3), a)) << endl;

    String result =
        (a += b) + "450501" + c + a(0, 2) +
        (b += a) +
        ((a == b) ? String("==") : String("!=")) +
        ((a != c) ? String("!=") : String("==")) +
        ((a < b) ? String("<") : String(">=")) +
        ((a > c) ? String(">") : String("<=")) +
        ((a <= b) ? String("<=") : String(">")) +
        ((a >= c) ? String(">=") : String("<")) +
        a(1, 3) +
        ++a;

    // cout << result << endl;

    // String result = "450501" + c;
    cout << result << endl;
}
