#include <iostream>
#include <stdexcept>
#include <cstdlib> // Dla std::abs i std::rand
#include <chrono>

// Klasa szablonowa dla tablicy haszującej z łańcuchowaniem
template <typename K, typename V>
class Chain_hash {
public:
    // Struktura dla każdego węzła w łańcuchach tablicy haszującej
    struct Node {
        K key;
        V value;
        Node* next;
        Node() : key(K()), value(V()), next(nullptr) {} // Domyślny konstruktor
        Node(K k, V val) : key(k), value(val), next(nullptr) {} // Konstruktor z parametrami
    };

private:
    int array_size;      // Rozmiar tablicy haszującej
    int elements;        // Liczba elementów w tablicy haszującej
    Node** array;        // Wskaźnik na tablicę wskaźników na węzły (tablica haszująca)

    // Funkcja haszująca do obliczania indeksu dla danego klucza
    int hash(K key) const {
        return std::abs(key) % array_size;
    }

    // Funkcja do ponownego haszowania tablicy, gdy współczynnik załadowania przekracza dopuszczalne wartości
    void rehash() {
        int old_size = array_size;
        array_size *= 2; // Podwojenie rozmiaru tablicy

        Node** new_array = new Node*[array_size](); // Utworzenie nowej tablicy o podwojonym rozmiarze
        Node** old_array = array; // Zachowanie starej tablicy

        array = new_array; // Przypisanie wskaźnika do nowej tablicy
        elements = 0; // Zresetowanie licznika elementów

        // Ponowne haszowanie wszystkich elementów ze starej tablicy do nowej
        for (int i = 0; i < old_size; ++i) {
            Node* current = old_array[i];
            while (current != nullptr) {
                Node* next = current->next;
                addElement(current->key, current->value); // Dodanie elementu do nowej tablicy
                delete current; // Usunięcie starego węzła
                current = next; // Przejście do następnego węzła
            }
        }

        delete[] old_array; // Usunięcie starej tablicy
    }

    // Utrzymanie górnego współczynnika załadowania
    void maintainLoadFactorTop() {
        float load_factor = static_cast<float>(elements) / static_cast<float>(array_size);
        if (load_factor > 0.75f) { // Jeśli współczynnik załadowania przekracza 0.75, ponowne haszowanie
            rehash();
        }
    }

    // Utrzymanie dolnego współczynnika załadowania
    void maintainLoadFactorBot() {
        float load_factor = static_cast<float>(elements) / static_cast<float>(array_size);
        if (load_factor < 0.25f) { // Jeśli współczynnik załadowania jest poniżej 0.25, ponowne haszowanie
            rehash();
        }
    }

public:
    // Konstruktor inicjalizujący tablicę haszującą z podanym rozmiarem
    Chain_hash(int size = 100) : array_size(size), elements(0) {
        array = new Node*[array_size](); // Inicjalizacja tablicy wskaźników nullptrami
    }

    // Destruktor czyszczący tablicę i usuwający tablicę wskaźników
    ~Chain_hash() {
        clear();
        delete[] array;
    }

    // Funkcja dodająca element do tablicy haszującej
    void addElement(K key, V value) {
        int pos = hash(key); // Obliczenie pozycji haszowania

        if (array[pos] == nullptr) { // Jeśli nie ma łańcucha na tej pozycji
            array[pos] = new Node(key, value); // Utworzenie nowego węzła
        } else {
            Node* current = array[pos]; // Przejście na koniec łańcucha
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(key, value); // Dodanie nowego węzła na końcu
        }

        elements++;
        maintainLoadFactorTop(); // Sprawdzenie, czy ponowne haszowanie jest potrzebne
    }

    // Funkcja usuwająca element z tablicy haszującej
    void removeElement(K key) {
        int pos = hash(key); // Obliczenie pozycji haszowania
        Node* current = array[pos];
        Node* prev = nullptr;

        while (current != nullptr) { // Przejście przez łańcuch, aby znaleźć węzeł
            if (current->key == key) {
                if (prev == nullptr) { // Jeśli węzeł do usunięcia jest pierwszym węzłem
                    array[pos] = current->next;
                } else { // Jeśli węzeł do usunięcia jest w środku lub na końcu
                    prev->next = current->next;
                }
                delete current; // Usunięcie węzła
                elements--;
                maintainLoadFactorBot(); // Sprawdzenie, czy ponowne haszowanie jest potrzebne
                return;
            }
            prev = current;
            current = current->next;
        }

        // Odkomentuj następną linię, aby rzucić wyjątek, jeśli element nie zostanie znaleziony
        // throw std::runtime_error("Element not found");
    }

    // Funkcja do wyświetlania elementów tablicy haszującej
    void print() const {
        std::cout << "Hash table: " << std::endl;
        for (int i = 0; i < array_size; i++) {
            Node* current = array[i];
            while (current != nullptr) {
                std::cout << "Key: " << current->key << ", Value: " << current->value << std::endl;
                current = current->next;
            }
        }
        std::cout << std::endl;
    }

    // Funkcja do czyszczenia tablicy haszującej
    void clear() {
        for (int i = 0; i < array_size; i++) {
            Node* current = array[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp; // Usunięcie wszystkich węzłów w łańcuchu
            }
            array[i] = nullptr; // Ustawienie początku łańcucha na nullptr
        }
        elements = 0; // Zresetowanie licznika elementów
    }
};
