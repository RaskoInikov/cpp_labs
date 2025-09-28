#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
    int *arr;
    int length;

  public:
    Array();
    Array(int length);
    Array(const Array &other);
    Array &operator=(const Array &other);
    ~Array();

    int get_length();
    void set_length(int length);
    void sort();
    bool isEmpty();

    bool contains(int value);

    Array get_intersection(Array &b);
    Array get_union(Array &b);

    friend std::ostream &operator<<(std::ostream &os, const Array &arr);
    friend std::istream &operator>>(std::istream &is, Array &arr);

  private:
    void quick_sort(int low, int high);
};

#endif
