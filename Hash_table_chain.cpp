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

    // Funkcja implementująca funkcję haszującą, aby znaleźć indeks dla klucza
    int computeHash(K key) const { return key % capacity; }

    void addElement(K key, V value)
    {
        int index = computeHash(key);
        Node<K, V>* newNode = new Node<K, V>(key, value);

        // Jeśli w danym indeksie jeszcze nie ma elementów
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            // Jeśli istnieje już lista w danym indeksie, dołącz na jej koniec
            Node<K, V>* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        currentSize++;
    }

    // Funkcja do usuwania pary klucz-wartość
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

    // Funkcja do wyświetlania przechowywanych par klucz-wartość
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


/*

int main()
{
    Map<int, int>* map = new Map<int, int>;

    map->addElement(1, 0);
    map->addElement(2, 1);
    map->addElement(4, 3);
    map->addElement(5, 4);
    map->addElement(6, 5);
    map->addElement(7, 6);
    map->addElement(21, 7); // Kollision z 1

    map->displayElements();
    cout << "Removed: " << map->removeElement(4) << endl;
    map->displayElements();
    delete map; // Zwolnij pamięć, aby uniknąć wycieków
    return 0;
}
 */