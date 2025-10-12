#ifndef ARRAY_H
#define ARRAY_H

class Array
{
private:
    int *data;
    int size;

public:
    Array();
    Array(int n);
    Array(const Array &other);
    Array &operator=(const Array &other);
    ~Array();

    bool contains(int value) const;
    bool contains(int value, int upto) const;
    bool is_empty() const;
    void input();
    void display() const;

    Array unique() const;
    Array merge(const Array &arr2) const;
    Array intersection(const Array &arr2);
    Array unionArrays(const Array &arr2);
};

#endif