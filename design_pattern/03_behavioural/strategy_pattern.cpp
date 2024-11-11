#include <iostream>
#include <vector>

// Strategy Interface
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0; // Pure virtual function for sorting
};
// Concrete Strategy: Bubble Sort
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Bubble Sort...\n";
        for (size_t i = 0; i < data.size() - 1; ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]); // Swap if elements are out of order
                }
            }
        }
    }
};

// Concrete Strategy: Quick Sort
class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "Using Quick Sort...\n";
        quickSort(data, 0, data.size() - 1);
    }

private:
    void quickSort(std::vector<int>& data, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(data, low, high);
            quickSort(data, low, pivotIndex - 1);
            quickSort(data, pivotIndex + 1, high);
        }
    }

    int partition(std::vector<int>& data, int low, int high) {
        int pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (data[j] < pivot) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
};
// Context
class Sorter {
private:
    SortStrategy* strategy; // Reference to a strategy object

public:
    Sorter(SortStrategy* initialStrategy) : strategy(initialStrategy) {}

    void setStrategy(SortStrategy* newStrategy) {
        strategy = newStrategy; // Change the strategy at runtime
    }

    void sort(std::vector<int>& data) {
        strategy->sort(data); // Delegate sorting to the current strategy
    }
};

int main() {
    std::vector<int> data = {5, 3, 8, 6, 2};

    // Use Bubble Sort
    SortStrategy* bubbleSort = new BubbleSort();
    Sorter sorter(bubbleSort);
    sorter.sort(data); // Sort using Bubble Sort
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Reset data and use Quick Sort
    data = {5, 3, 8, 6, 2};
    SortStrategy* quickSort = new QuickSort();
    sorter.setStrategy(quickSort); // Change strategy to Quick Sort
    sorter.sort(data); // Sort using Quick Sort
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Clean up
    delete bubbleSort;
    delete quickSort;

    return 0;
}
