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

