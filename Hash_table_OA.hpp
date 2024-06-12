#include <bits/stdc++.h>
using namespace std;

// Szablon dla typu generycznego
template <typename K, typename V>

// Nasza własna klasa Map
class Open_address {
public:
    class Node {
    public:
        V value;
        K key;
        Node() : key(K()), value(V()) {}
        // Konstruktor Node
        Node(K key, V value) {
            this->value = value;
            this->key = key;
        }
    };

private:
    int capacity;      // Size of the hash table
    int currentSize;        // Number of elements in the hash table
    Node* table;        // Hash table
    Node dummyNode;

    int hash(K key) const {
        return std::abs(key) % capacity;
    }

    void rehash(int new_capacity) {
        int old_size = capacity;
        capacity = new_capacity;

        Node* new_table = new Node[capacity]();
        Node* old_table = table;

        table = new_table;
        currentSize = 0;

        for (int i = 0; i < old_size; ++i) {
            if (old_table[i].key != K() && old_table[i].key != dummyNode.key) {
                addElement(old_table[i].key, old_table[i].value);
            }
        }

        delete[] old_table;
    }

    void maintainLoadFactorTop() {
        float load_factor = static_cast<float>(currentSize) / static_cast<float>(capacity);
        if (load_factor > 0.75f) {
            rehash(capacity*2);
        }
    }
    void maintainLoadFactorBot() {
        float load_factor = static_cast<float>(currentSize) / static_cast<float>(capacity);
        if (load_factor < 0.25f && capacity > 10) {  // Prevent rehashing to a very small size
            rehash(capacity/2);
        }
    }

public:
    Open_address(int size = 100) : capacity(size), currentSize(0) {
        table = new Node[capacity]();
        dummyNode = Node(K(), V());
    }

    // Funkcja do dodawania pary klucz-wartość
    void addElement(K key, V value) {
        Node newNode(key, value);

        // Zastosuj funkcję haszującą, aby znaleźć indeks dla podanego klucza
        int index = hash(key);

        // Znajdź następne wolne miejsce
        while (table[index].key != K() && table[index].key != key && table[index].key != dummyNode.key) {
            index++;
            index %= capacity;
        }

        // Jeśli nowy węzeł ma być wstawiony, zwiększ aktualny rozmiar
        if (table[index].key == K() || table[index].key == dummyNode.key) {
            currentSize++;
            maintainLoadFactorTop();
        }

        table[index] = newNode;
    }

    // Funkcja do usuwania pary klucz-wartość
    V removeElement(K key) {
        // Zastosuj funkcję haszującą, aby znaleźć indeks dla podanego klucza
        int index = hash(key);

        // Znajdź węzeł z podanym kluczem
        while (table[index].key != K()) {
            // Jeśli znaleziono węzeł
            if (table[index].key == key) {
                Node temp = table[index];

                // Wstaw tutaj węzeł dummy do dalszego użycia
                table[index] = dummyNode;

                // Zmniejsz rozmiar
                currentSize--;
                maintainLoadFactorBot();
                return temp.value;
            }
            index++;
            index %= capacity;
        }

        // Jeśli nie znaleziono, zwróć domyślną wartość typu V
        //throw std::runtime_error("Element not found");
    }

    void clear() {
        delete[] table;
        table = new Node[capacity]();
        currentSize = 0;
    }

    ~Open_address() {
        delete[] table;
    }
};