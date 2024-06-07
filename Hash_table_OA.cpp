#include <bits/stdc++.h>
#include "dynamic_array.cpp"
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

    void rehash() {
        int old_size = capacity;
        capacity *= 2;

        Node* new_array = new Node[capacity]();
        Node* old_array = table;

        table = new_array;
        currentSize = 0;

        for (int i = 0; i < old_size; ++i) {
            if (old_array[i].key != K()) {
                addElement(old_array[i].key, old_array[i].value);
            }
        }

        delete[] old_array;
    }

    void maintainLoadFactorTop() {
        float load_factor = static_cast<float>(currentSize) / static_cast<float>(capacity);
        if (load_factor > 0.75f) {
            rehash();
        }
    }

    void maintainLoadFactorBot() {
        float load_factor = static_cast<float>(currentSize) / static_cast<float>(capacity);
        if (load_factor < 0.25f) {
            rehash();
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
        while (table[index].key != K()
               && table[index].key != key
               && table[index].key != dummyNode.key) {
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