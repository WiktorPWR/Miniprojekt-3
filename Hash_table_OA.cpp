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

public:
    Open_address()
    {
        // Początkowa pojemność tablicy haszowanej
        capacity = 20;
        currentSize = 0;
        for (int i = 0; i < capacity; i++)
            table.push_back(nullptr);

    }

    // Funkcja implementująca funkcję haszującą, aby znaleźć indeks dla klucza
    int computeHash(K key) const { return key % capacity; }




};