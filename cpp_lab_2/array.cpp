#include "array.h"
#include <iostream>

Array::Array() : data(nullptr), size(0) {}

Array::Array(int n) : size(n)
{
    if (size > 0)
    {
        data = new int[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = 0;
        }
    }
    else
    {
        data = nullptr;
        size = 0;
    }
}

Array::Array(const Array &other) : size(other.size)
{
    if (size > 0)
    {
        data = new int[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    else
    {
        data = nullptr;
    }
}

Array::~Array()
{
    delete[] data;
}

Array &Array::operator=(const Array &other)
{
    if (this != &other)
    {
        delete[] data;

        size = other.size;
        if (size > 0)
        {
            data = new int[size];
            for (int i = 0; i < size; i++)
            {
                data[i] = other.data[i];
            }
        }
        else
        {
            data = nullptr;
        }
    }
    return *this;
}

void Array::input()
{
    if (size == 0)
    {
        std::cout << "Array is empty, cannot input elements.\n";
        return;
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter element " << i + 1 << ": ";
        std::cin >> data[i];
    }
}

void Array::display() const
{
    if (is_empty())
    {
        std::cout << "[ ]" << std::endl;
        return;
    }

    std::cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        std::cout << data[i] << " ";
    }
    std::cout << "]" << std::endl;
}

Array Array::intersection(const Array &arr2)
{
    if (this->is_empty() || arr2.is_empty())
        return Array(0);

    Array temp(this->size);
    int count = 0;

    for (int i = 0; i < this->size; i++)
        if (arr2.contains(this->data[i]) && !temp.contains(this->data[i], count))
            temp.data[count++] = this->data[i];

    temp.size = count;
    return temp;
}

Array Array::unionArrays(const Array &arr2)
{
    if (this->is_empty())
        return arr2.unique();
    if (arr2.is_empty())
        return this->unique();

    return this->merge(arr2).unique();
}

bool Array::is_empty() const
{
    return size == 0;
}

Array Array::unique() const
{
    if (this->is_empty())
        return Array(0);

    Array temp(this->size);
    int count = 0;

    for (int i = 0; i < this->size; i++)
    {
        if (!temp.contains(this->data[i], count))
        {
            temp.data[count++] = this->data[i];
        }
    }

    Array result(count);
    for (int i = 0; i < count; i++)
        result.data[i] = temp.data[i];

    return result;
}

bool Array::contains(int value) const
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->data[i] == value)
            return true;
    }
    return false;
}

bool Array::contains(int value, int upto) const
{
    for (int i = 0; i < upto && i < this->size; i++)
    {
        if (this->data[i] == value)
            return true;
    }
    return false;
}

Array Array::merge(const Array &arr2) const
{
    Array result(this->size + arr2.size);
    for (int i = 0; i < this->size; i++)
        result.data[i] = this->data[i];
    for (int j = 0; j < arr2.size; j++)
        result.data[this->size + j] = arr2.data[j];
    return result;
}
