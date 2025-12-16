#pragma once
#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

#include "MyException.h"

class InputException : public MyException
{
    char err[20];

public:
    InputException(const char *msg, int c, const char *e = "INPUT_ERROR")
        : MyException(c, msg)
    {
        strncpy(err, e, 19);
        err[19] = '\0';
    }

    void printCause() const override
    {
        std::cerr << "InputException [" << code << "] "
                  << err << ": " << message;
    }
};

#endif
