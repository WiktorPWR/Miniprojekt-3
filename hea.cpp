#include <iostream>
#include <stdexcept> // Dla std::out_of_range

template <typename T>
class Heap {
private:
    T* heap_array;
    int capacity;
    int size;

    void heapify_up(int index) {
        if (index <= 0)
            return;

        int parent = (index - 1) / 2;
        if (heap_array[parent] > heap_array[index]) {
            std::swap(heap_array[parent], heap_array[index]);
            heapify_up(parent);
        }
    }

    void heapify_down(int index) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int smallest = index;

        if (left_child < size && heap_array[left_child] < heap_array[smallest])
            smallest = left_child;
        if (right_child < size && heap_array[right_child] < heap_array[smallest])
            smallest = right_child;

        if (smallest != index) {
            std::swap(heap_array[index], heap_array[smallest]);
            heapify_down(smallest);
        }
    }

    void resize(int new_capacity) {
        T* new_heap_array = new T[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_heap_array[i] = heap_array[i];
        }
        delete[] heap_array;
        heap_array = new_heap_array;
        capacity = new_capacity;
    }

public:
    Heap() : heap_array(nullptr), capacity(0), size(0) {}

    ~Heap() {
        delete[] heap_array;
    }

    void insert(const T& value) {
        if (size == capacity) {
            int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        heap_array[size++] = value;
        heapify_up(size - 1);
    }

    T extract_min() {
        if (size == 0) {
            throw std::out_of_range("Heap is empty");
        }

        T min_value = heap_array[0];
        heap_array[0] = heap_array[--size];
        heapify_down(0);
        return min_value;
    }

    bool empty() const {
        return size == 0;
    }
};