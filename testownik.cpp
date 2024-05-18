#include <iostream>
#include "C:\Users\WiktorJankowski-Ostr\Miniprojekt-3\Cuckoo_hashing.cpp"
#include "string"
int main() {
    Cuckoo_hashing<std::string> hash_table;

    // Tworzenie i wstawianie struktur Node
    hash_table.insert({"Bozena", 10});
    hash_table.insert({"Ala", 2});
    hash_table.insert({"Zosia", 12});
    hash_table.insert({"Marek", 22});

    hash_table.print();

    // Usuwanie elementu
    hash_table.remove({"Zosia", 12});
    hash_table.print();

    return 0;
}
