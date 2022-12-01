#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

using std::size_t;

template<typename T> class Vector {
    enum {CHUNK = 10};
    size_t capacity;    // Size of the current array allocation (total number of ints, in use or not)
    size_t n_elems;     // Number of int spaces currently in use, starting from position 0
    T* data_ptr;      // Pointer to the heap array
    void grow() {
        capacity *= 1.6;
        T new_array[capacity];
        for (int i = 0; i < n_elems; i++) {
            new_array[i] = data_ptr[i];
        }
//    delete[] data_ptr;
        data_ptr = &*new_array;
    };
public:
    // Object Mgt.
    Vector<T>() {
        data_ptr = new T[CHUNK];
        capacity = CHUNK;
        n_elems = 0;
    };
    Vector<T>(const Vector& v) {
        data_ptr = v.data_ptr;
        capacity = v.capacity;
        n_elems = v.n_elems;
    };            // Copy constructor
    Vector& operator=(const Vector& v) {
        data_ptr = v.data_ptr;
        capacity = v.capacity;
        n_elems = v.n_elems;
        return *this;
    }; // Copy assignment operator
    ~Vector() {
        delete [] data_ptr;
    };

    // Accessors
    T front() const {
        if (this->empty()) {
            throw std::range_error("");
        }
        return data_ptr[0];
    };                  // Return the int in position 0, if any
    T back() const {
        if (this->empty()) {
            throw std::range_error("");
        }
        return data_ptr[n_elems -1];
    };                   // Return last element (position n_elems-1)
    T at(size_t pos) const {
        if (this->empty() || pos >= n_elems) {
            throw std::range_error("");
        }
        return data_ptr[pos];
    };           // Return element in position "pos" (0-based)
    size_t size() const {
        return n_elems;
    };                // Return n_elems
    bool empty() const {
        if (this->n_elems == 0) {
            return true;
        }
        return false;
    };                 // Return n_elems == 0

    // Mutators
    T& operator[](size_t pos) {
        return data_ptr[pos];
    };        // Same as at but no bounds checking
    void push_back(T item) {
        if (n_elems == capacity) {
            grow();
        }
        data_ptr[n_elems] = item;
        n_elems++;
    };           // Append a new element at the end of the array
    void pop_back() {
        if (this->empty()) {
            throw std::range_error("");
        }
        --n_elems;
    };                    // --n_elems (nothing else to do; returns nothing)
    void erase(size_t pos) {
        if (this->empty() || pos >= n_elems) {
            throw std::range_error("");
        }
        for (auto i = pos; i < n_elems; i++) {
            data_ptr[i] = data_ptr[i + 1];
        }
        n_elems--;
    };             // Remove item in position pos and shuffles following items left
    void insert(size_t pos, T item) {
        if (n_elems == capacity) {
            grow();
        }
        for (auto i = pos; i < n_elems; i++) {
            data_ptr[i + 1] = data_ptr[i];
        }
        data_ptr[pos] = item;
        n_elems++;
    };  // Shuffle items right to make room for a new element
    void clear() {
        n_elems = 0;
    };                       // n_elems = 0 (nothing else to do; keep the current capacity)

    // Iterators
    T* begin() {
        return data_ptr;
    };                       // Return a pointer to 1st element, or nullptr if n_elems == 0
    T* end() {
        return &data_ptr[n_elems];
    };                         // Return a pointer to 1 past last element, or nullptr if n_elems == 0

    // Comparators
    bool operator==(const Vector& v) const {
        return data_ptr == v.data_ptr && capacity == v.capacity && n_elems == v.n_elems;
    };
    bool operator!=(const Vector& v) const {
        return !(data_ptr == v.data_ptr && capacity == v.capacity && n_elems == v.n_elems);
    };
};

#endif