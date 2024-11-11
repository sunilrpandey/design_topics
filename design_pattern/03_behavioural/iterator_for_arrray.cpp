#include <iostream>

// Iterator Interface
template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;       // Check if there are more elements
    virtual T next() = 0;             // Return the next element
};

// Concrete Iterator for an Array
template<typename T>
class ArrayIterator : public Iterator<T> {
private:
    T* array;           // Pointer to the array
    int size;           // Size of the array
    int currentIndex;   // Current index in the array

public:
    ArrayIterator(T* arr, int s) : array(arr), size(s), currentIndex(0) {}

    bool hasNext() override {
        return currentIndex < size;   // True if we haven't reached the end
    }

    T next() override {
        if (!hasNext()) {
            throw std::out_of_range("No more elements in the array");
        }
        return array[currentIndex++];  // Return the current element and move to the next
    }
};

// Client code to demonstrate the Array Iterator
int main() {
    int arr[] = {1, 2, 3, 4, 5};   // An example array
    int size = sizeof(arr) / sizeof(arr[0]);

    ArrayIterator<int> iterator(arr, size);

    // Iterate through the array
    while (iterator.hasNext()) {
        std::cout << iterator.next() << " ";
    }

    std::cout << "\n";

    return 0;
}
