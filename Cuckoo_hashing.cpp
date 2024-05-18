#include <iostream>      // Biblioteka do wejścia/wyjścia
#include <stdexcept>     // Biblioteka do wyjątków
#include <string>        // Biblioteka do obsługi stringów

// Szablon klasy Cuckoo_hashing
template <typename T>
class Cuckoo_hashing {
public: // Sekcja publiczna klasy
    // Definicja struktury Node
    struct Node {
        T value;      // Pole do przechowywania wartości
        int key;      // Pole do przechowywania klucza
        Node() : key(-1), value(T()) {} // Domyślny konstruktor ustawiający domyślne wartości
        Node(T val, int k) : value(val), key(k) {} // Konstruktor z parametrami inicjalizujący pola
    };

private: // Sekcja prywatna klasy
    int array_size = 10;  // Początkowy rozmiar tablicy
    int elements = 0;     // Liczba elementów w tablicy
    Node* array_1;        // Wskaźnik na pierwszą tablicę
    Node* array_2;        // Wskaźnik na drugą tablicę

    // Funkcja hashująca 1
    int hash1(int key) {
        return key % array_size;  // Zwraca indeks tablicy na podstawie klucza
    }

    // Funkcja hashująca 2
    int hash2(int key) {
        return (key / array_size + key) % array_size;  // Zwraca inny indeks tablicy na podstawie klucza
    }

    // Funkcja do ponownego haszowania (rozszerzania tablicy)
    void rehash() {
        int old_size = array_size;    // Przechowuje stary rozmiar tablicy
        array_size *= 2;              // Podwaja rozmiar tablicy

        Node* newlist_1 = new Node[array_size];  // Tworzy nową, większą pierwszą tablicę
        Node* newlist_2 = new Node[array_size];  // Tworzy nową, większą drugą tablicę
        Node* buffer = new Node[elements];       // Tworzy bufor do przechowywania elementów

        int iterator = 0;
        for (int i = 0; i < old_size; i++) {
            if (array_1[i].key != -1) {
                buffer[iterator++] = array_1[i]; // Kopiuje elementy z pierwszej tablicy do bufora
            }
            if (array_2[i].key != -1) {
                buffer[iterator++] = array_2[i]; // Kopiuje elementy z drugiej tablicy do bufora
            }
        }

        delete[] array_1; // Usuwa starą pierwszą tablicę
        delete[] array_2; // Usuwa starą drugą tablicę
        array_1 = newlist_1; // Przypisuje nową pierwszą tablicę
        array_2 = newlist_2; // Przypisuje nową drugą tablicę

        elements = 0;  // Resetuje licznik elementów przed ponownym wstawieniem
        for (int j = 0; j < iterator; j++) {
            insert(buffer[j]); // Ponownie wstawia elementy z bufora do nowych tablic
        }

        delete[] buffer; // Usuwa bufor
    }

public:
    // Konstruktor klasy Cuckoo_hashing
    Cuckoo_hashing() {
        array_1 = new Node[array_size]; // Inicjalizuje pierwszą tablicę
        array_2 = new Node[array_size]; // Inicjalizuje drugą tablicę
    }

    // Destruktor klasy Cuckoo_hashing
    ~Cuckoo_hashing() {
        delete[] array_1; // Usuwa pierwszą tablicę
        delete[] array_2; // Usuwa drugą tablicę
    }

    // Funkcja do wstawiania elementu
    void insert(Node node) {
        int count = 0;
        int max_iterations = array_size * 4; // Ustawia maksymalną liczbę iteracji

        while (count < max_iterations) {
            int pos1 = hash1(node.key); // Oblicza pozycję w pierwszej tablicy

            if (array_1[pos1].key == -1) { // Sprawdza, czy pozycja jest wolna
                array_1[pos1] = node; // Wstawia element do pierwszej tablicy
                elements++; // Zwiększa licznik elementów
                return;
            }

            Node temp_1 = array_1[pos1]; // Zapisuje element do tymczasowej zmiennej
            array_1[pos1] = node; // Wstawia nowy element do pierwszej tablicy
            int pos2 = hash2(temp_1.key); // Oblicza pozycję w drugiej tablicy

            if (array_2[pos2].key == -1) { // Sprawdza, czy pozycja jest wolna
                array_2[pos2] = temp_1; // Wstawia tymczasowy element do drugiej tablicy
                elements++; // Zwiększa licznik elementów
                return;
            }

            node = array_2[pos2]; // Przypisuje element do zmiennej node
            array_2[pos2] = temp_1; // Wstawia tymczasowy element do drugiej tablicy
            count++; // Zwiększa licznik iteracji
        }

        rehash(); // Jeśli osiągnięto maksymalną liczbę iteracji, wywołuje rehash
        insert(node); // Ponownie próbuje wstawić element
    }

    // Funkcja do usuwania elementu
    void remove(Node node) {
        int pos1 = hash1(node.key); // Oblicza pozycję w pierwszej tablicy
        int pos2 = hash2(node.key); // Oblicza pozycję w drugiej tablicy

        if (array_1[pos1].key == node.key) { // Sprawdza, czy element jest w pierwszej tablicy
            array_1[pos1].key = -1; // Ustawia klucz na -1 (usuwa element)
            array_1[pos1].value = T(); // Resetuje wartość
            return;
        }

        if (array_2[pos2].key == node.key) { // Sprawdza, czy element jest w drugiej tablicy
            array_2[pos2].key = -1; // Ustawia klucz na -1 (usuwa element)
            array_2[pos2].value = T(); // Resetuje wartość
            return;
        }

        throw std::runtime_error("Element not found"); // Rzuca wyjątkiem, jeśli element nie został znaleziony
    }

    // Funkcja do drukowania zawartości tablic
    void print() {
        std::cout << "First array: " << std::endl;
        for (int i = 0; i < array_size; i++) {
            std::cout << array_1[i].key << " " << array_1[i].value << ", "; // Drukuje zawartość pierwszej tablicy
        }
        std::cout << std::endl;

        std::cout << "Second array: " << std::endl;
        for (int i = 0; i < array_size; i++) {
            std::cout << array_2[i].key << " " << array_2[i].value << ", "; // Drukuje zawartość drugiej tablicy
        }
        std::cout << std::endl;
    }
};


