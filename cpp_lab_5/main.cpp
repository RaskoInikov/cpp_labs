#include <iostream>
#include "template/Interface.h"

int main()
{
    try
    {
        Interface iface;
        iface.menu();
    }
    catch (...)
    {
        std::cerr << "Unexpected fatal error\n";
    }

    std::cout << "Exiting.\n";
    return 0;
}
