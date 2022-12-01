#include <iostream>
#include "vector.h"

void Vector::grow() {
    capacity *= 1.6;
    int new_array[capacity];
    for (int i = 0; i < n_elems; i++) {
        new_array[i] = data_ptr[i];
    }
//    delete[] data_ptr;
    data_ptr = &*new_array;
}

Vector::Vector() {
    data_ptr = new int[CHUNK];
    capacity = CHUNK;
    n_elems = 0;
}

Vector::Vector(const Vector &v) {
    data_ptr = v.data_ptr;
    capacity = v.capacity;
    n_elems = v.n_elems;
}

Vector &Vector::operator=(const Vector &v) {
    data_ptr = v.data_ptr;
    capacity = v.capacity;
    n_elems = v.n_elems;
    return *this;
}

Vector::~Vector() {
    delete [] data_ptr;
    std::cout << "hi";
}

int Vector::front() const {
    if (this->empty()) {
        throw std::range_error("");
    }
    return data_ptr[0];
}

int Vector::back() const {
    if (this->empty()) {
        throw std::range_error("");
    }
    return data_ptr[n_elems -1];
}

int Vector::at(size_t pos) const {
    if (this->empty() || pos >= n_elems) {
        throw std::range_error("");
    }
    return data_ptr[pos];
}

size_t Vector::size() const {
    return n_elems;
}

bool Vector::empty() const {
    if (this->n_elems == 0) {
        return true;
    }
    return false;
}

int &Vector::operator[](size_t pos) {
    return data_ptr[pos];
}

void Vector::push_back(int item) {
    if (n_elems == capacity) {
        grow();
    }
    data_ptr[n_elems] = item;
    n_elems++;

}

void Vector::pop_back() {
    if (this->empty()) {
        throw std::range_error("");
    }
    --n_elems;
}

void Vector::erase(size_t pos) {
    if (this->empty() || pos >= n_elems) {
        throw std::range_error("");
    }
    for (int i = pos; i < n_elems; i++) {
        data_ptr[i] = data_ptr[i + 1];
    }
    n_elems--;
}

void Vector::insert(size_t pos, int item) {
    if (n_elems == capacity) {
        grow();
    }
    for (int i = pos; i < n_elems; i++) {
        data_ptr[i + 1] = data_ptr[i];
    }
    data_ptr[pos] = item;
    n_elems++;
}

void Vector::clear() {
    n_elems = 0;
}

int *Vector::begin() {
    return data_ptr;
}

int *Vector::end() {
    return &data_ptr[n_elems];
}

bool Vector::operator==(const Vector &v) const {
    return data_ptr == v.data_ptr && capacity == v.capacity && n_elems == v.n_elems;
}

bool Vector::operator!=(const Vector &v) const {
    return !(data_ptr == v.data_ptr && capacity == v.capacity && n_elems == v.n_elems);
}
