#include <iostream>
#include <stdexcept>
#include <algorithm> // For std::distance()

// Custom Vector class
template<typename T>
class Vector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    // Constructor
    Vector() : data(nullptr), size(0), capacity(0) {}

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Add an element to the vector
    void push_back(const T& value) {
        if (size == capacity) {
            // Reallocate memory if necessary
            capacity = capacity == 0 ? 1 : capacity * 2;
            T* newData = new T[capacity];

            // Copy the old data
            for (size_t i = 0; i < size; ++i) {
                newData[i] = data[i];
            }

            // Free the old data
            delete[] data;
            data = newData;
        }

        data[size++] = value;
    }

    // Get the size of the vector
    size_t getSize() const {
        return size;
    }

    // Get an element by index
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Get a constant reference to an element (read-only)
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Forward declaration of iterator class
    class VectorIterator;

    // Return an iterator to the beginning of the vector
    VectorIterator begin() {
        return VectorIterator(data);
    }

    // Return an iterator to the end of the vector
    VectorIterator end() {
        return VectorIterator(data + size);
    }

    // Custom find function using iterator
    VectorIterator find(const T& value) {
        for (VectorIterator it = begin(); it != end(); ++it) {
            if (*it == value) {
                return it;
            }
        }
        return end(); // Return end() if not found
    }

    // Iterator class
    class VectorIterator {
    private:
        T* ptr; // Pointer to the current element

    public:
        // Constructor
        VectorIterator(T* p) : ptr(p) {}

        // Dereference operator
        T& operator*() {
            return *ptr;
        }

        // Pre-increment operator (++it)
        VectorIterator& operator++() {
            ++ptr;
            return *this;
        }

        // Post-increment operator (it++)
        VectorIterator operator++(int) {
            VectorIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Equality operator
        bool operator==(const VectorIterator& other) const {
            return ptr == other.ptr;
        }

        // Inequality operator
        bool operator!=(const VectorIterator& other) const {
            return ptr != other.ptr;
        }
    };
};

// Client code to demonstrate the Vector and Iterator
int main() {
    // Create a custom Vector of integers
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);

    // Iterate through the Vector using begin() and end()
    std::cout << "Vector elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Find an element in the Vector
    int searchValue = 30;
    auto it = vec.find(searchValue);
    if (it != vec.end()) {
        std::cout << "Found value " << searchValue << " in the vector.\n";
    } else {
        std::cout << "Value " << searchValue << " not found in the vector.\n";
    }

    // Try finding a value that doesn't exist
    searchValue = 100;
    it = vec.find(searchValue);
    if (it != vec.end()) {
        std::cout << "Found value " << searchValue << " in the vector.\n";
    } else {
        std::cout << "Value " << searchValue << " not found in the vector.\n";
    }

    return 0;
}
