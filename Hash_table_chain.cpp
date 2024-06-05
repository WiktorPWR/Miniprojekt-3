#include <iostream>
#include "dynamic_array.cpp"
using namespace std;

template <typename K, typename V>
class Node {
public:
    V value;
    K key;
    Node<K, V>* next;

    // Konstruktor Node
    Node(K key, V value)
    {
        this->value = value;
        this->key = key;
        this->next = nullptr;
    }
};

template <typename K, typename V>
class Chain_hash {
    DynamicArray<Node<K, V>*> table;
    int capacity;
    int currentSize;

public:
    Chain_hash(int initialCapacity = 1000)
    {
        capacity = initialCapacity;
        currentSize = 0;
        for (int i = 0; i < capacity; i++)
            table.push_back(nullptr);
    }

    int computeHash(K key) const { return key % capacity; }

    void addElement(K key, V value)
    {
        int index = computeHash(key);
        Node<K, V>* newNode = new Node<K, V>(key, value);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node<K, V>* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        currentSize++;
    }

    V removeElement(K key)
    {
        int index = computeHash(key);
        Node<K, V>* current = table[index];
        Node<K, V>* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                V value = current->value;
                delete current;
                currentSize--;
                return value;
            }
            prev = current;
            current = current->next;
        }
        return V(); // Jeśli nie znaleziono
    }

    void displayElements() const
    {
        for (int i = 0; i < capacity; i++) {
            Node<K, V>* current = table[i];
            while (current != nullptr) {
                cout << "key = " << current->key
                     << "  value = " << current->value
                     << endl;
                current = current->next;
            }
        }
    }

    // Funkcja czyszcząca całą listę
    void clear() {
        for (int i = 0; i < capacity; i++) {
            Node<K, V>* current = table[i];
            while (current != nullptr) {
                Node<K, V>* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        currentSize = 0;
    }

    // Destruktor
    ~Chain_hash()
    {
        clear();
    }
};

// int main()
// {
//     Map<int, int> map;

//     map.addElement(1, 0);
//     map.addElement(2, 1);
//     map.addElement(4, 3);
//     map.addElement(5, 4);
//     map.addElement(6, 5);
//     map.addElement(7, 6);
//     map.addElement(21, 7); // Kolizja z 1

//     map.displayElements();
//     cout << "Removed: " << map.removeElement(4) << endl;
//     map.displayElements();
//     map.clear(); // Czyszczenie listy
//     map.displayElements();
//     return 0;
// }
