#include <iostream>
#include <stdexcept>
#include <cstdlib> // For std::abs and std::rand
#include <chrono>

template <typename T>
class RobinHoodHashing {
public:
    struct Node {
        int key;
        T value;
        int probe_length;
        Node() : key(-1), value(T()), probe_length(0) {}
        Node(int k, T val, int pl = 0) : key(k), value(val), probe_length(pl) {}
    };

private:
    int array_size;      // Size of the hash table
    int elements;        // Number of elements in the hash table
    Node* array;         // Hash table

    int hash(int key) const {
        return std::abs(key) % array_size;
    }

    void rehash() {
        int old_size = array_size;
        array_size *= 2;

        Node* new_array = new Node[array_size];
        Node* old_array = array;

        array = new_array;
        elements = 0;

        for (int i = 0; i < old_size; ++i) {
            if (old_array[i].key != -1) {
                insert(old_array[i]);
            }
        }

        delete[] old_array;
    }

    void maintainLoadFactor() {
        float load_factor = static_cast<float>(elements) / static_cast<float>(array_size);
        if (load_factor > 0.5f) {
            rehash();
        }
    }

public:
    RobinHoodHashing(int size = 100) : array_size(size), elements(0) {
        array = new Node[array_size];
    }

    ~RobinHoodHashing() {
        delete[] array;
    }

    void insert(Node node) {
        int pos = hash(node.key);
        int probe_length = 0;

        while (true) {
            if (array[pos].key == -1) {
                array[pos] = Node(node.key, node.value, probe_length);
                elements++;
                maintainLoadFactor();
                return;
            }

            if (array[pos].probe_length < probe_length) {
                std::swap(node.key, array[pos].key);
                std::swap(node.value, array[pos].value);
                std::swap(probe_length, array[pos].probe_length);
            }

            pos = (pos + 1) % array_size;
            probe_length++;
        }
    }

    void remove(Node node) {
        int pos = hash(node.key);
        int probe_length = 0;

        while (array[pos].key != -1 && probe_length <= array[pos].probe_length) {
            if (array[pos].key == node.key) {
                array[pos].key = -1;
                elements--;
                return;
            }
            pos = (pos + 1) % array_size;
            probe_length++;
        }

        throw std::runtime_error("Element not found");
    }

    void print() const {
        std::cout << "Hash table: " << std::endl;
        for (int i = 0; i < array_size; i++) {
            if (array[i].key != -1) {
                std::cout << "Key: " << array[i].key << ", Value: " << array[i].value << ", Probe Length: " << array[i].probe_length << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void clear() {
        delete[] array;
        array = new Node[array_size];
        elements = 0;
    }
};


