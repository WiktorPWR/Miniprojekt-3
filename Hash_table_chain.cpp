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

// Nasza własna klasa Map
class Map {
    // Tablica elementów haszowanych
    DynamicArray<Node<K, V>*> table;
    int capacity;
    // Aktualny rozmiar
    int currentSize;

public:
    Map(int initialCapacity = 10)
    {
        capacity = initialCapacity;
        currentSize = 0;
        for (int i = 0; i < capacity; i++)
            table.push_back(nullptr);
    }

    // Destruktor
    ~Map()
    {
        for (int i = 0; i < capacity; i++) {
            Node<K, V>* current = table[i];
            while (current != nullptr) {
                Node<K, V>* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

int main()
{
    Map<int, int>* map = new Map<int, int>;

    delete map; // Zwolnij pamięć, aby uniknąć wycieków
    return 0;
}