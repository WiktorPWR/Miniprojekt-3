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
    hash_table.insert({"Lech", 5});
    hash_table.insert({"Wanda", 15});
    hash_table.insert({"Kazimierz", 25});
    hash_table.insert({"Bronislaw", 35});
    hash_table.insert({"Danuta", 45});
    hash_table.insert({"Ewa", 55});
    hash_table.insert({"Gosia", 65});
    hash_table.insert({"Hanna", 75});
    hash_table.insert({"Igor", 85});
    hash_table.insert({"Jadwiga", 95});
    hash_table.insert({"Krzysztof", 105});
    hash_table.insert({"Lucja", 115});
    hash_table.print();
    // hash_table.insert({"Mikolaj", 125});
    // hash_table.insert({"Nina", 135});
    // hash_table.insert({"Olek", 145});
    // hash_table.insert({"Pawel", 155});
    // hash_table.insert({"Rafal", 165});
    // hash_table.insert({"Sylwia", 175});
    // hash_table.insert({"Tomasz", 185});
    // hash_table.insert({"Urszula", 195});
    // hash_table.insert({"Wieslaw", 205});

    //hash_table.print();

    // Usuwanie elementu
    //hash_table.remove({"Zosia", 12});
    //hash_table.print();

    return 0;
}
