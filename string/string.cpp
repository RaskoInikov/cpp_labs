#include "string.h"
#include "cstring"
#include <iostream>
#include <cctype>

String::String() : data(nullptr), length(0), capacity(0)
{
    allocate(1);
    data[0] = '\0';
}

String::String(const char *str) : data(nullptr), length(0), capacity(0)
{
    if (str != nullptr)
    {
        length = strlen(str);
        allocate(length + 1);
        strcpy(data, str);
    }
    else
    {
        allocate(1);
        data[0] = '\0';
    }
}

String::String(const String &other) : data(nullptr), length(other.length), capacity(other.capacity)
{
    if (this != &other)
    {
        allocate(capacity);
        strcpy(data, other.data);
    }
}

String::~String() { delete[] data; }

String String::operator+(const String &other)
{
    String new_string;
    new_string.reallocate(this->length + other.length + 1);
    new_string.data[new_string.capacity] = '\0';
    new_string.length = this->length + other.length;

    if (this->length > 0)
    {
        std::strcpy(new_string.data, this->data);
    }

    if (other.length > 0)
    {
        std::strcat(new_string.data, other.data);
    }

    return new_string;
}

String &String::operator+=(const String &other)
{
    // if (other.length <= 0)
    // {
    //     return *this;
    // }

    // unsigned int new_length = this->length + other.length;
    // if (new_length + 1 > this->capacity)
    // {
    //     reallocate(new_length + 1);
    // }

    // std::strcat(data, other.data);
    // this->length = new_length;

    // return *this;
    return *this = *this + other;
}

String &String::operator=(const String &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] data;

    length = other.length;
    capacity = other.capacity;

    if (other.data != nullptr)
    {
        data = new char[capacity];
        std::strcpy(data, other.data);
    }
    else
    {
        data = nullptr;
    }

    return *this;
}

String String::operator()(int start, int end)
{
    if (start < 0 || start >= this->length || end < start || end > this->length)
    {
        return String();
    }

    int substr_length = end - start;
    String sub_string;
    sub_string.allocate(substr_length + 1);

    for (int i = 0; i < substr_length; i++)
    {
        sub_string.data[i] = this->data[start + i];
    }

    sub_string.data[substr_length] = '\0';
    sub_string.length = substr_length;

    return sub_string;
}

bool String::operator==(const String &other) { return std::strcmp(this->data, other.data) == 0; }

bool String::operator!=(const String &other) { return std::strcmp(this->data, other.data) != 0; }

bool String::operator<(const String &other) { return std::strcmp(this->data, other.data) < 0; }

bool String::operator>(const String &other) { return std::strcmp(this->data, other.data) > 0; }

bool String::operator<=(const String &other) { return std::strcmp(this->data, other.data) <= 0; }

bool String::operator>=(const String &other) { return std::strcmp(this->data, other.data) >= 0; }

char String::operator[](unsigned int index)
{
    if (index < 0 || index >= length)
    {
        return '\0';
    }

    return data[index];
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    for (int i = 0; i < s.length; i++)
    {
        os << s.data[i];
    }

    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    const size_t BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];

    is >> buffer;

    delete[] s.data;

    s.length = std::strlen(buffer);
    s.capacity = s.length + 1;
    s.data = new char[s.capacity];

    std::strcpy(s.data, buffer);

    return is;
}

String &String::operator++()
{
    toUpperCase();
    return *this;
}

String &String::operator--()
{
    trim();
    return *this;
}

unsigned int String::len() { return length; }

unsigned int String::cap() { return capacity; }

char *String::c_str() { return data; }

void String::clear()
{
    allocate(1);
    data[0] = '\0';
}

bool String::contains(char c)
{
    for (int i = 0; i < capacity; i++)
    {
        if (c == data[i])
        {
            return true;
        }
    }

    return false;
}

bool String::contains(char *str)
{
    int strLength = std::strlen(str);

    if (strLength == 0)
        return true;
    if (length < strLength)
        return false;
    if (strLength > length)
        return false;

    for (unsigned int i = 0; i <= length - strLength; i++)
    {
        unsigned int j = 0;
        while (j < strLength && data[i + j] == str[j])
        {
            j++;
        }
        if (j == strLength)
            return true;
    }

    return false;
}

bool String::contains(String &str)
{
    if (str.length == 0)
        return true;
    if (length < str.length)
        return false;
    if (str.length > length)
        return false;

    for (int i = 0; i <= length - str.length; i++)
    {
        int j = 0;
        while (j < str.length && data[i + j] == str.data[j])
        {
            j++;
        }
        if (j == str.length)
            return true;
    }

    return false;
}

void String::allocate(unsigned int new_capacity)
{
    delete[] data;
    data = new char[new_capacity];
    capacity = new_capacity;
}

void String::reallocate(unsigned int new_capacity)
{
    char *new_data = new char[new_capacity];
    if (data != nullptr)
    {
        strcpy(new_data, data);
        delete[] data;
    }

    data = new_data;
    capacity = new_capacity;
}

void String::toUpperCase()
{
    for (unsigned int i = 0; i < length; i++)
    {
        data[i] = std::toupper(data[i]);
    }
}

void String::toLowerCase()
{
    for (unsigned int i = 0; i < length; i++)
    {
        data[i] = std::tolower(data[i]);
    }
}

void String::trim()
{
    if (length == 0)
        return;

    unsigned int start = 0;
    while (start < length && std::isspace(data[start]))
    {
        start++;
    }

    unsigned int end = length;
    while (end > start && std::isspace(data[end - 1]))
    {
        end--;
    }

    if (start > 0 || end < length)
    {
        unsigned int new_length = end - start;
        char *new_data = new char[new_length + 1];

        for (unsigned int i = 0; i < new_length; i++)
        {
            new_data[i] = data[start + i];
        }
        new_data[new_length] = '\0';

        delete[] data;
        data = new_data;
        length = new_length;
        capacity = new_length + 1;
    }
}