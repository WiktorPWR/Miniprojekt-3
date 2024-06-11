#include <bits/stdc++.h>
#include "dynamic_array.cpp"
using namespace std;

// Szablon dla typu generycznego
template <typename K, typename V>

// Nasza własna klasa Map
class Open_address {
public:
    // Klasa węzła (Node)
    class Node {
    public:
        V value;
        K key;
        Node() : key(K()), value(V()) {} // Domyślny konstruktor
        // Konstruktor Node z parametrami
        Node(K key, V value) {
            this->value = value;
            this->key = key;
        }
    };

private:
    int capacity;      // Rozmiar tablicy haszującej
    int currentSize;   // Liczba elementów w tablicy haszującej
    Node* table;       // Tablica haszująca
    Node dummyNode;    // Węzeł pomocniczy (dummyNode)

    // Funkcja haszująca do obliczania indeksu dla danego klucza
    int hash(K key) const {
        return std::abs(key) % capacity;
    }

    // Funkcja do ponownego haszowania tablicy, gdy współczynnik załadowania przekracza dopuszczalne wartości
    void rehash() {
        int old_size = capacity;
        capacity *= 2; // Podwojenie rozmiaru tablicy

        Node* new_array = new Node[capacity](); // Utworzenie nowej tablicy o podwojonym rozmiarze
        Node* old_array = table; // Zachowanie starej tablicy

        table = new_array; // Przypisanie wskaźnika do nowej tablicy
        currentSize = 0; // Zresetowanie licznika elementów

        // Ponowne haszowanie wszystkich elementów ze starej tablicy do nowej
        for (int i = 0; i < old_size; ++i) {
            if (old_array[i].key != K()) { // Jeśli klucz nie jest domyślny (niepusty)
                addElement(old_array[i].key, old_array[i].value); // Dodanie elementu do nowej tablicy
            }
        }

        delete[] old_array; // Usunięcie starej tablicy
    }

    // Utrzymanie górnego współczynnika załadowania
    void maintainLoadFactorTop() {
        float load_factor = static_cast<float>(currentSize) / static_cast<float>(capacity);
        if (load_factor > 0.75f) { // Jeśli współczynnik załadowania przekracza 0.75, ponowne haszowanie
            rehash();
        }
    }

    // Utrzymanie dolnego współczynnika załadowania
    void maintainLoadFactorBot() {
        float load_factor = static_cast<float>(currentSize) / static_cast<float>(capacity);
        if (load_factor < 0.25f) { // Jeśli współczynnik załadowania jest poniżej 0.25, ponowne haszowanie
            rehash();
        }
    }

public:
    // Konstruktor inicjalizujący tablicę haszującą z podanym rozmiarem
    Open_address(int size = 100) : capacity(size), currentSize(0) {
        table = new Node[capacity](); // Inicjalizacja tablicy wskaźników nullptrami
        dummyNode = Node(K(), V()); // Inicjalizacja węzła dummyNode
    }

    // Funkcja do dodawania pary klucz-wartość
    void addElement(K key, V value) {

        Node newNode(key, value); // Utworzenie nowego węzła

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
            maintainLoadFactorTop(); // Sprawdzenie, czy ponowne haszowanie jest potrzebne
        }

        table[index] = newNode; // Wstawienie nowego węzła
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
                maintainLoadFactorBot(); // Sprawdzenie, czy ponowne haszowanie jest potrzebne
                return temp.value;
            }
            index++;
            index %= capacity;
        }

        // Jeśli nie znaleziono, zwróć domyślną wartość typu V
        // throw std::runtime_error("Element not found");
    }

    // Funkcja do czyszczenia tablicy haszującej
    void clear() {
        delete[] table;
        table = new Node[capacity](); // Utworzenie nowej tablicy
        currentSize = 0; // Zresetowanie licznika elementów
    }

    // Destruktor czyszczący tablicę i usuwający tablicę wskaźników
    ~Open_address() {
        delete[] table;
    }
};
