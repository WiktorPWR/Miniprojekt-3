#include <iostream>
#include <stdexcept>

template<typename T>
class Heap {
private:
    T* heap_array; // Array storing heap elements
    int capacity;  // Capacity of the heap (maximum number of elements)
    int size;      // Current size of the heap

    // Helper function: moves element up the heap (up)
    void heapify_up(int index) {
        if (index <= 0)
            return;

        int parent = (index - 1) / 2;
        if (heap_array[parent] > heap_array[index]) {
            std::swap(heap_array[parent], heap_array[index]);
            heapify_up(parent);
        }
    }

    // Helper function: moves element down the heap (down)
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

    // Helper function: resizes the array
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
    // Constructor
    Heap() : heap_array(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Heap() {
        delete[] heap_array;
    }

    // Method: inserts an element into the heap
    void insert(const T& value) {
        if (size == capacity) {
            int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        heap_array[size++] = value;
        heapify_up(size - 1);
    }

    // Method: removes and returns the smallest element from the heap
    T extract_min() {
        if (size == 0) {
            throw std::out_of_range("Heap is empty");
        }

        T min_value = heap_array[0];
        heap_array[0] = heap_array[--size];
        heapify_down(0);
        return min_value;
    }

    // Method: returns true if the heap is empty, otherwise false
    bool empty() const {
        return size == 0;
    }

    // Method: returns the current size of the heap
    int get_size() const {
        return size;
    }

    // Method: returns the element at the given index (for direct access)
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return heap_array[index];
    }

    // Method: prints the heap contents
    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << "(" << heap_array[i].key << ", " << heap_array[i].value << ") ";
        }
    }
};

template <typename T>
class Hash_table_BST {
public:
    struct Node {
        T value;
        int key;
        Node() : key(-1) {} // Default constructor setting default values
        Node(T val, int k) : value(val), key(k) {} // Constructor with parameters initializing fields

        // Define comparison operators
        bool operator<(const Node& other) const {
            return key < other.key;
        }

        bool operator>(const Node& other) const {
            return key > other.key;
        }
    };

private:
    int array_size;  // Initial size of the array
    int elements;    // Number of elements in the table
    Heap<Node>* array;

    int hash(int key) const {
        return (key / array_size + key) % array_size;
    }

    void resize(int new_size) {
        Heap<Node>* new_array = new Heap<Node>[new_size];
        for (int i = 0; i < array_size; ++i) {
            while (!array[i].empty()) {
                Node node = array[i].extract_min();
                int index = (node.key / new_size + node.key) % new_size;
                new_array[index].insert(node);
            }
        }
        delete[] array;
        array = new_array;
        array_size = new_size;
    }

    void check_load_factor_and_resize() {
        if (elements >= array_size * 0.75) {
            resize(array_size * 2);
        }
    }

public:
    Hash_table_BST(int size = 20) : array_size(size), elements(0) {
        array = new Heap<Node>[array_size];
    }

    ~Hash_table_BST() {
        delete[] array;
    }

    void insert(const Node& node) {
        check_load_factor_and_resize();
        int index = hash(node.key);
        array[index].insert(node);
        ++elements;
    }

    void remove(int key) {
        int index = hash(key);
        if (array[index].empty()) {
            throw std::out_of_range("Key not found");
        }

        // Temporary array to hold elements while searching for the key
        int heap_size = array[index].get_size();
        Node* temp_array = new Node[heap_size];
        int temp_size = 0;

        // Remove all elements from the heap and search for the key
        bool key_found = false;
        while (!array[index].empty()) {
            Node minNode = array[index].extract_min();
            if (minNode.key == key) {
                key_found = true;
                --elements;
            } else {
                temp_array[temp_size++] = minNode;
            }
        }

        if (!key_found) {
            delete[] temp_array;
            throw std::out_of_range("Key not found");
        }

        // Re-insert all other elements back into the heap
        for (int i = 0; i < temp_size; ++i) {
            array[index].insert(temp_array[i]);
        }

        delete[] temp_array;
    }

    // Method: prints the hash table contents
    void print() const {
        for (int i = 0; i < array_size; ++i) {
            std::cout << "Bucket " << i << ": ";
            array[i].print();
            std::cout << std::endl;
        }
    }
    void clear() 
    {
    delete[] array; // Usuwa tablicę haszującą
    array = new Heap<Node>[array_size]; // Tworzy nową, pustą tablicę haszującą
    elements = 0; // Resetuje liczbę elementów
    }
};