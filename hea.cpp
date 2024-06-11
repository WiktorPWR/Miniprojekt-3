#include <iostream>
#include <stdexcept> // Dla std::out_of_range

// Szablonowa klasa reprezentująca kopiec
template <typename T>
class Heap {
private:
    T* heap_array; // Tablica przechowująca elementy kopca
    int capacity;  // Pojemność kopca (maksymalna liczba elementów)
    int size;      // Aktualny rozmiar kopca

    // Funkcja pomocnicza: przesuwa element w górę kopca (heapify up)
    void heapify_up(int index) {
        if (index <= 0) // Jeśli indeks jest mniejszy lub równy 0, zakończ
            return;

        int parent = (index - 1) / 2; // Oblicz indeks rodzica
        if (heap_array[parent] > heap_array[index]) { // Jeśli rodzic jest większy niż bieżący element
            std::swap(heap_array[parent], heap_array[index]); // Zamień elementy miejscami
            heapify_up(parent); // Rekurencyjnie wywołaj heapify_up dla rodzica
        }
    }

    // Funkcja pomocnicza: przesuwa element w dół kopca (heapify down)
    void heapify_down(int index) {
        int left_child = 2 * index + 1; // Indeks lewego dziecka
        int right_child = 2 * index + 2; // Indeks prawego dziecka
        int smallest = index; // Indeks najmniejszego elementu

        if (left_child < size && heap_array[left_child] < heap_array[smallest]) // Jeśli lewe dziecko jest mniejsze niż bieżący element
            smallest = left_child;
        if (right_child < size && heap_array[right_child] < heap_array[smallest]) // Jeśli prawe dziecko jest mniejsze niż bieżący element
            smallest = right_child;

        if (smallest != index) { // Jeśli najmniejszy element nie jest bieżącym elementem
            std::swap(heap_array[index], heap_array[smallest]); // Zamień elementy miejscami
            heapify_down(smallest); // Rekurencyjnie wywołaj heapify_down dla najmniejszego elementu
        }
    }

    // Funkcja pomocnicza: zmienia rozmiar tablicy
    void resize(int new_capacity) {
        T* new_heap_array = new T[new_capacity]; // Utwórz nową tablicę o nowej pojemności
        for (int i = 0; i < size; ++i) {
            new_heap_array[i] = heap_array[i]; // Skopiuj elementy do nowej tablicy
        }
        delete[] heap_array; // Usuń starą tablicę
        heap_array = new_heap_array; // Przypisz wskaźnik nowej tablicy do wskaźnika kopca
        capacity = new_capacity; // Zaktualizuj pojemność
    }

public:
    // Konstruktor inicjalizujący pusty kopiec
    Heap() : heap_array(nullptr), capacity(0), size(0) {}

    // Destruktor czyszczący pamięć zajmowaną przez kopiec
    ~Heap() {
        delete[] heap_array;
    }

    // Metoda: wstawia element do kopca
    void insert(const T& value) {
        if (size == capacity) { // Jeśli kopiec jest pełny
            int new_capacity = (capacity == 0) ? 1 : capacity * 2; // Podwój pojemność (lub ustaw na 1, jeśli była 0)
            resize(new_capacity); // Zmień rozmiar tablicy
        }
        heap_array[size++] = value; // Dodaj nowy element na końcu kopca
        heapify_up(size - 1); // Przesuń element w górę, aby zachować właściwości kopca
    }

    // Metoda: usuwa i zwraca najmniejszy element z kopca
    T extract_min() {
        if (size == 0) { // Jeśli kopiec jest pusty
            throw std::out_of_range("Heap is empty"); // Rzuć wyjątek
        }

        T min_value = heap_array[0]; // Zapisz najmniejszy element (na górze kopca)
        heap_array[0] = heap_array[--size]; // Przenieś ostatni element na górę i zmniejsz rozmiar kopca
        heapify_down(0); // Przesuń element w dół, aby zachować właściwości kopca
        return min_value; // Zwróć najmniejszy element
    }

    // Metoda: zwraca true, jeśli kopiec jest pusty, w przeciwnym razie false
    bool empty() const {
        return size == 0; // Kopiec jest pusty, jeśli rozmiar jest równy 0
    }
};
