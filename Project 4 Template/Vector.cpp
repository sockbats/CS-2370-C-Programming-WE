#include <iostream>
#include "Vector.h"

template<typename T> void Vector<T>::grow() {
    capacity *= 1.6;
    T new_array[capacity];
    for (int i = 0; i < n_elems; i++) {
        new_array[i] = data_ptr[i];
    }
//    delete[] data_ptr;
    data_ptr = &*new_array;
}

template<typename T> Vector<T>::Vector() {
    data_ptr = new T[CHUNK];
    capacity = CHUNK;
    n_elems = 0;
}

template<typename T> Vector<T>::Vector(const Vector &v) {
    data_ptr = v.data_ptr;
    capacity = v.capacity;
    n_elems = v.n_elems;
}

template<typename T>Vector &Vector<T>::operator=(const Vector &v) {
    data_ptr = v.data_ptr;
    capacity = v.capacity;
    n_elems = v.n_elems;
    return *this;
}

template<typename T> Vector<T>::~Vector() {
    delete [] data_ptr;
}

template<typename T> T Vector<T>::front() const {
    if (this->empty()) {
        throw std::range_error("");
    }
    return data_ptr[0];
}

template<typename T> T Vector<T>::back() const {
    if (this->empty()) {
        throw std::range_error("");
    }
    return data_ptr[n_elems -1];
}

template<typename T> T Vector<T>::at(size_t pos) const {
    if (this->empty() || pos >= n_elems) {
        throw std::range_error("");
    }
    return data_ptr[pos];
}

template<typename T> size_t Vector<T>::size() const {
    return n_elems;
}

template<typename T> bool Vector<T>::empty() const {
    if (this->n_elems == 0) {
        return true;
    }
    return false;
}

template<typename T> T &Vector<T>::operator[](size_t pos) {
    return data_ptr[pos];
}

template<typename T> void Vector<T>::push_back(T item) {
    if (n_elems == capacity) {
        grow();
    }
    data_ptr[n_elems] = item;
    n_elems++;
}

template<typename T> void Vector<T>::pop_back() {
    if (this->empty()) {
        throw std::range_error("");
    }
    --n_elems;
}

template<typename T> void Vector<T>::erase(size_t pos) {
    if (this->empty() || pos >= n_elems) {
        throw std::range_error("");
    }
    for (auto i = pos; i < n_elems; i++) {
        data_ptr[i] = data_ptr[i + 1];
    }
    n_elems--;
}

template<typename T> void Vector<T>::insert(size_t pos, T item) {
    if (n_elems == capacity) {
        grow();
    }
    for (auto i = pos; i < n_elems; i++) {
        data_ptr[i + 1] = data_ptr[i];
    }
    data_ptr[pos] = item;
    n_elems++;
}

template<typename T> void Vector<T>::clear() {
    n_elems = 0;
}

template<typename T> T *Vector<T>::begin() {
    return data_ptr;
}

template<typename T> T *Vector<T>::end() {
    return &data_ptr[n_elems];
}

template<typename T> bool Vector<T>::operator==(const Vector &v) const {
    return data_ptr == v.data_ptr && capacity == v.capacity && n_elems == v.n_elems;
}

template<typename T> bool Vector<T>::operator!=(const Vector &v) const {
    return !(data_ptr == v.data_ptr && capacity == v.capacity && n_elems == v.n_elems);
}

