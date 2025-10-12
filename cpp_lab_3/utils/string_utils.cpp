#include "string_utils.h"

int stringToInt(const String &s)
{
    int res = 0;
    bool neg = false;
    unsigned int i = 0;
    char c = s[i];
    if (c == '-')
    {
        neg = true;
        i = 1;
    }
    for (;; ++i)
    {
        c = s[i];
        if (c == '\0')
            break;
        if (c >= '0' && c <= '9')
            res = res * 10 + (c - '0');
        else
            break;
    }
    return neg ? -res : res;
}
