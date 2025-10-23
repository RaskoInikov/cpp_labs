#include "string.h"
#include <cstring>
#include <cctype>

String::String() : data(new char[1]), length(0)
{
    data[0] = '\0';
}

String::String(const char *str)
{
    if (str)
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    else
    {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
}

String::String(const String &other) : length(other.length)
{
    data = new char[length + 1];
    strcpy(data, other.data);
}

String::~String() { delete[] data; }

String::String(String &&other) noexcept
    : data(other.data), length(other.length)
{
    other.data = nullptr;
    other.length = 0;
}

String String::operator+(const String &other) const
{
    String res;
    res.length = length + other.length;
    res.data = new char[res.length + 1];
    strcpy(res.data, data);
    strcat(res.data, other.data);
    return res;
}

String String::operator+(const char *other) const
{
    // if (!other)
    //     return *this;
    // String res;
    // unsigned int otherLen = strlen(other);
    // res.length = length + otherLen;
    // res.data = new char[res.length + 1];
    // strcpy(res.data, data);
    // strcat(res.data, other);
    // return res;
    return *this + String(other);
}

String operator+(const char *lhs, const String &rhs)
{
    // if (!lhs)
    //     return rhs;
    // unsigned int lhsLen = strlen(lhs);
    // String res;
    // res.length = lhsLen + rhs.length;
    // res.data = new char[res.length + 1];
    // strcpy(res.data, lhs);
    // strcat(res.data, rhs.data);
    // return res;
    return String(lhs) + rhs;
}

String &String::operator+=(const String &other)
{
    *this = *this + other;
    return *this;
}

String &String::operator=(const String &other)
{
    if (this == &other)
        return *this;
    delete[] data;
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
    return *this;
}

String &String::operator=(String &&other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        length = other.length;

        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}

String String::operator()(int start, int end)
{
    if (start < 0 || start >= (int)length || end < start || end > (int)length)
        return String();
    int sublen = end - start;
    char *buf = new char[sublen + 1];
    strncpy(buf, data + start, sublen);
    buf[sublen] = '\0';
    String res(buf);
    delete[] buf;
    return res;
}

bool String::operator==(const String &other) { return strcmp(data, other.data) == 0; }
bool String::operator!=(const String &other) { return strcmp(data, other.data) != 0; }
bool String::operator<(const String &other) { return strcmp(data, other.data) < 0; }
bool String::operator>(const String &other) { return strcmp(data, other.data) > 0; }
bool String::operator<=(const String &other) { return strcmp(data, other.data) <= 0; }
bool String::operator>=(const String &other) { return strcmp(data, other.data) >= 0; }

char String::operator[](unsigned int index) const
{
    if (index >= length)
        return '\0';
    return data[index];
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s.data;
    return os;
}

std::istream &operator>>(std::istream &is, String &obj)
{
    if (obj.data != nullptr)
        delete[] obj.data;

    const int BUFFER_SIZE = 80;
    char buffer[BUFFER_SIZE];

    is.getline(buffer, BUFFER_SIZE);

    obj.length = strlen(buffer);
    obj.data = new char[obj.length + 1];
    strcpy(obj.data, buffer);

    return is;
}

String &String::operator++()
{
    for (unsigned int i = 0; i < length; i++)
        data[i] += 1;
    return *this;
}

String &String::operator--()
{
    for (unsigned int i = 0; i < length; i++)
        data[i] -= 1;
    return *this;
}