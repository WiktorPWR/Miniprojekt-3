#include <iostream>
#include <stdexcept>
#include <cstdlib> // For std::abs and std::rand
#include <chrono>

template <typename K, typename V>
class Chain_hash {
public:
    struct Node {
        K key;
        V value;
        Node* next;
        Node() : key(K()), value(V()), next(nullptr) {}
        Node(K k, V val) : key(k), value(val), next(nullptr) {}
    };

private:
    int array_size;      // Size of the hash table
    int elements;        // Number of elements in the hash table
    Node** array;        // Hash table

    int hash(K key) const {
        // Ulepszona funkcja haszująca
        return key % array_size;
    }

    void rehash(int new_array_size) {
        int old_size = array_size;
        array_size = new_array_size;

        Node** new_array = new Node*[array_size]();
        Node** old_array = array;

        array = new_array;
        elements = 0;

        for (int i = 0; i < old_size; ++i) {
            Node* current = old_array[i];
            while (current != nullptr) {
                Node* next = current->next;
                addElement(current->key, current->value);
                delete current;
                current = next;
            }
        }

        delete[] old_array;
    }


    void maintainLoadFactorTop() {
        float load_factor = static_cast<float>(elements) / static_cast<float>(array_size);
        if (load_factor > 0.75f) {
            rehash(array_size*2);
        }
    }

    void maintainLoadFactorBot() {
        float load_factor = static_cast<float>(elements) / static_cast<float>(array_size);
        if (load_factor < 0.25f) {
            rehash(array_size/2);
        }
    }

public:
    Chain_hash(int size = 100) : array_size(size), elements(0) {
        array = new Node*[array_size]();
    }

    ~Chain_hash() {
        clear();
        delete[] array;
    }

    void addElement(K key, V value) {
        int pos = hash(key);

        if (array[pos] == nullptr) {
            array[pos] = new Node(key, value);
        } else {
            Node* current = array[pos];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(key, value);
        }

        elements++;
        maintainLoadFactorTop();
    }

    void removeElement(K key) {
        int pos = hash(key);
        Node* current = array[pos];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    array[pos] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                elements--;
                maintainLoadFactorBot();
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void print() const {
        std::cout << "Hash table: " << std::endl;
        for (int i = 0; i < array_size; i++) {
            Node* current = array[i];
            while (current != nullptr) {
                std::cout << "Key: " << current->key << ", Value: " << current->value << std::endl;
                current = current->next;
            }
        }
        std::cout << std::endl;
    }

    void clear() {
        for (int i = 0; i < array_size; i++) {
            Node* current = array[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            array[i] = nullptr;
        }
        elements = 0;
    }
};