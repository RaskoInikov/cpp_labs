#include "array.h"

#include <iostream>

Array::Array() {
    length = 0;
    arr = nullptr;
}

Array::Array(int length) {
    this->length = length;
    arr = new int[length];
}

Array::Array(const Array &other) {
    length = other.length;
    arr = new int[length];

    for (int i = 0; i < length; i++) {
        arr[i] = other.arr[i];
    }
}

Array &Array::operator=(const Array &other) {
    if (this == &other) {
        return *this;
    }

    delete[] arr;

    length = other.length;
    arr = new int[length];

    for (int i = 0; i < length; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

Array::~Array() { delete[] arr; }

int Array::get_length() { return length; }

void Array::set_length(int length) {
    this->length = length;
    delete[] arr;

    arr = new int[length];
}

void Array::quick_sort(int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quick_sort(low, pi - 1);
        quick_sort(pi + 1, high);
    }
}

bool Array::isEmpty() { return (arr == nullptr || length == 0); }

void Array::sort() {
    if (arr == nullptr || length <= 1) {
        return;
    }
    quick_sort(0, length - 1);
}

bool Array::contains(int value) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == value) {
            return true;
        }
    }

    return false;
}

Array Array::get_intersection(Array &b) {
    int size = std::min(this->length, b.length);
    Array temp(size);
    int resultSize = 0;

    for (int i = 0; i < this->length; i++) {
        int current = this->arr[i];

        bool isResultContains = false;
        for (int j = 0; j < resultSize; j++) {
            if (temp.arr[j] == current) {
                isResultContains = true;
                break;
            }
        }

        if (!isResultContains && b.contains(current)) {
            temp.arr[resultSize++] = current;
        }
    }

    Array result(resultSize);
    for (int i = 0; i < resultSize; i++) {
        result.arr[i] = temp.arr[i];
    }

    return result;
}

Array Array::get_union(Array &b) {
    int size = this->length + b.length;
    Array temp(size);
    int resultSize = 0;

    for (int i = 0; i < this->length; i++) {
        int current = this->arr[i];

        bool isResultContains = false;
        for (int j = 0; j < resultSize; j++) {
            if (temp.arr[j] == current) {
                isResultContains = true;
                break;
            }
        }

        if (!isResultContains) {
            temp.arr[resultSize++] = current;
        }
    }

    for (int i = 0; i < b.length; i++) {
        int current = b.arr[i];

        bool isResultContains = false;
        for (int j = 0; j < resultSize; j++) {
            if (temp.arr[j] == current) {
                isResultContains = true;
                break;
            }
        }

        if (!isResultContains) {
            temp.arr[resultSize++] = current;
        }
    }

    Array result(resultSize);
    for (int i = 0; i < resultSize; i++) {
        result.arr[i] = temp.arr[i];
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const Array &arr) {
    if (arr.arr == nullptr || arr.length == 0) {
        os << "Array is empty!";
        return os;
    }

    os << "[ ";
    for (int i = 0; i < arr.length; i++) {
        os << arr.arr[i] << " ";
    }
    os << "]" << std::endl;

    return os;
}

std::istream &operator>>(std::istream &is, Array &arr) {
    if (arr.length == 0) {
        return is;
    }

    for (int i = 0; i < arr.length; i++) {
        is >> arr.arr[i];
    }

    return is;
}
