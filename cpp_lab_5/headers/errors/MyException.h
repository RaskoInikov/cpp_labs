#pragma once
#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>
#include <cstring>

class MyException
{
protected:
    int code;
    char message[80];

public:
    MyException(int c = 0, const char *msg = "")
        : code(c)
    {
        strncpy(message, msg, 79);
        message[79] = '\0';
    }

    virtual ~MyException() = default;

    int getCode() const { return code; }
    const char *getMessage() const { return message; }

    virtual void printCause() const
    {
        std::cerr << "Error [" << code << "]: " << message;
    }
};

#endif
