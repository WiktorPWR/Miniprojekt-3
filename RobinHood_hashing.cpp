#include <iostream>
#include <stdexcept>
#include <cstdlib> // Dla std::abs i std::rand
#include <chrono>

// Szablonowa klasa RobinHoodHashing implementująca haszowanie metodą Robin Hood
template <typename T>
class RobinHoodHashing {
public:
    // Struktura reprezentująca węzeł w tablicy haszującej
    struct Node {
        int key; // Klucz
        T value; // Wartość
        int probe_length; // Długość próby (odległość od początkowej pozycji haszowania)
        Node() : key(-1), value(T()), probe_length(0) {} // Domyślny konstruktor
        Node(int k, T val, int pl = 0) : key(k), value(val), probe_length(pl) {} // Konstruktor z parametrami
    };

private:
    int array_size;      // Rozmiar tablicy haszującej
    int elements;        // Liczba elementów w tablicy haszującej
    Node* array;         // Tablica haszująca

    // Funkcja haszująca do obliczania indeksu dla danego klucza
    int hash(int key) const {
        unsigned int ukey = static_cast<unsigned int>(key);
        ukey = (ukey ^ 0xdeadbeef) + (ukey << 4) + 0x42;
        return static_cast<int>(ukey % static_cast<unsigned int>(array_size));
    }

    // Funkcja do ponownego haszowania tablicy, gdy współczynnik załadowania przekracza dopuszczalne wartości
    void rehash() {
        int old_size = array_size;
        array_size *= 2; // Podwojenie rozmiaru tablicy

        Node* new_array = new Node[array_size]; // Utworzenie nowej tablicy o podwojonym rozmiarze
        Node* old_array = array; // Zachowanie starej tablicy

        array = new_array; // Przypisanie wskaźnika do nowej tablicy
        elements = 0; // Zresetowanie licznika elementów

        // Ponowne haszowanie wszystkich elementów ze starej tablicy do nowej
        for (int i = 0; i < old_size; ++i) {
            if (old_array[i].key != -1) { // Jeśli klucz nie jest domyślny (niepusty)
                insert(old_array[i]); // Dodanie elementu do nowej tablicy
            }
        }

        delete[] old_array; // Usunięcie starej tablicy
    }

    // Utrzymanie współczynnika załadowania
    void maintainLoadFactor() {
        float load_factor = static_cast<float>(elements) / static_cast<float>(array_size);
        if (load_factor > 0.5f) { // Jeśli współczynnik załadowania przekracza 0.5, ponowne haszowanie
            rehash();
        }
    }

public:
    // Konstruktor inicjalizujący tablicę haszującą z podanym rozmiarem
    RobinHoodHashing(int size = 100) : array_size(size), elements(0) {
        array = new Node[array_size]; // Inicjalizacja tablicy wskaźników domyślnymi węzłami
    }

    // Destruktor czyszczący tablicę i usuwający tablicę wskaźników
    ~RobinHoodHashing() {
        delete[] array;
    }

    // Funkcja wstawiająca element do tablicy haszującej
    void insert(Node node) {
        int pos = hash(node.key); // Obliczenie pozycji haszowania
        int probe_length = 0; // Inicjalizacja długości próby

        while (true) {
            if (array[pos].key == -1) { // Jeśli znaleziono pustą pozycję
                array[pos] = Node(node.key, node.value, probe_length); // Wstawienie nowego węzła
                elements++;
                maintainLoadFactor(); // Sprawdzenie, czy ponowne haszowanie jest potrzebne
                return;
            }

            if (array[pos].probe_length < probe_length) { // Jeśli długość próby wstawianego elementu jest większa
                std::swap(node.key, array[pos].key); // Zamiana kluczy
                std::swap(node.value, array[pos].value); // Zamiana wartości
                std::swap(probe_length, array[pos].probe_length); // Zamiana długości prób
            }

            pos = (pos + 1) % array_size; // Przejście do następnej pozycji
            probe_length++;
        }
    }

    // Funkcja usuwająca element z tablicy haszującej
    void remove(Node node) {
        int pos = hash(node.key); // Obliczenie pozycji haszowania
        int probe_length = 0; // Inicjalizacja długości próby

        while (array[pos].key != -1 && probe_length <= array[pos].probe_length) {
            if (array[pos].key == node.key) { // Jeśli znaleziono węzeł do usunięcia
                array[pos].key = -1; // Ustawienie klucza na -1 (oznaczenie jako usunięty)
                elements--;
                return;
            }
            pos = (pos + 1) % array_size; // Przejście do następnej pozycji
            probe_length++;
        }

        throw std::runtime_error("Element not found"); // Rzucenie wyjątku, jeśli element nie został znaleziony
    }

    // Funkcja wyświetlająca elementy tablicy haszującej
    void print() const {
        std::cout << "Hash table: " << std::endl;
        for (int i = 0; i < array_size; i++) {
            if (array[i].key != -1) { // Jeśli klucz nie jest domyślny (niepusty)
                std::cout << "Key: " << array[i].key << ", Value: " << array[i].value << ", Probe Length: " << array[i].probe_length << std::endl;
            }
        }
        std::cout << std::endl;
    }

    // Funkcja czyszcząca tablicę haszującą
    void clear() {
        delete[] array;
        array = new Node[array_size]; // Utworzenie nowej tablicy
        elements = 0; // Zresetowanie licznika elementów
    }
};
