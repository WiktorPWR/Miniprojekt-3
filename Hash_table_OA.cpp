#include <bits/stdc++.h>
#include "dynamic_array.cpp"
using namespace std;

// Szablon dla typu generycznego
template <typename K, typename V>

// Klasa Node
class Node {
public:
    V value;
    K key;

    // Konstruktor Node
    Node(K key, V value)
    {
        this->value = value;
        this->key = key;

    }
};

// Szablon dla typu generycznego
template <typename K, typename V>

// Nasza własna klasa Map
class Open_address {
    // Tablica elementów haszowanych
    DynamicArray<Node<K, V>*> table;
    int capacity;
    // Aktualny rozmiar
    int currentSize;
    // Węzeł dummy
    Node<K, V>* dummyNode;

public:
    Open_address()
    {
        // Początkowa pojemność tablicy haszowanej
        capacity = 20;
        currentSize = 0;
        for (int i = 0; i < capacity; i++)
            table.push_back(nullptr);

        dummyNode = new Node<K, V>(-1, -1);
    }

    // Funkcja implementująca funkcję haszującą, aby znaleźć indeks dla klucza
    int computeHash(K key) const { return key % capacity; }

    // Funkcja do dodawania pary klucz-wartość
    void addElement(K key, V value)
    {
        Node<K, V>* newNode = new Node<K, V>(key, value);

        // Zastosuj funkcję haszującą, aby znaleźć indeks dla podanego klucza
        int index = computeHash(key);

        // Znajdź następne wolne miejsce
        while (table[index] != nullptr
               && table[index]->key != key
               && table[index]->key != -1) {
            index++;
            index %= capacity;
        }

        // Jeśli nowy węzeł ma być wstawiony, zwiększ aktualny rozmiar
        if (table[index] == nullptr || table[index]->key == -1)
            currentSize++;
        table[index] = newNode;
    }

    // Funkcja do usuwania pary klucz-wartość
    V removeElement(int key)
    {
        // Zastosuj funkcję haszującą, aby znaleźć indeks dla podanego klucza
        int index = computeHash(key);

        // Znajdź węzeł z podanym kluczem
        while (table[index] != nullptr) {
            // Jeśli znaleziono węzeł
            if (table[index]->key == key) {
                Node<K, V>* temp = table[index];

                // Wstaw tutaj węzeł dummy do dalszego użycia
                table[index] = dummyNode;

                // Zmniejsz rozmiar
                currentSize--;
                return temp->value;
            }
            index++;
            index %= capacity;
        }

        // Jeśli nie znaleziono, zwróć NULL
        return V();
    }

    void clear() {
        delete table;
    }

    ~Open_address(){
        clear();
    }


};