#include <iostream>
#include "C:\Users\WiktorJankowski-Ostr\Miniprojekt-3\RobinHood_hashing.cpp"
#include "string"
#include "C:\Users\WiktorJankowski-Ostr\Miniprojekt-3\Hash_table_with_BST.cpp"
#include <cstdlib>
#include <chrono>

int main() {
    srand((unsigned) time(NULL));
    RobinHoodHashing<int> hash_table_robin_hood;
    Hash_table_BST<int> hash_table_BST;

    const int ilosc_powtorzen = 1000;
    int ilosc_elemtow[] = {5000, 8000, 10000, 16000, 20000, 40000, 60000};
    double time_insert_robin_hood = 0;
    double time_remove_robin_hood = 0;
    double time_insert_BST = 0;
    double time_remove_BST = 0;

    for (int elemnty : ilosc_elemtow) {
        for (int i = 0; i <= ilosc_powtorzen; i++) {
            // Utworzenie tablicy elementów
            for (int j = 0; j <= elemnty; j++) {
                int random_value = rand();
                int random_key = rand();
                hash_table_robin_hood.insert({random_value, random_key});
                // hash_table_BST.insert({random_value, random_key});
                // std::cout << "Dodanie elementu " << j << std::endl;
            }
            
            // Testy
            int random_value = rand();
            int random_key = rand();
            
            // Test operacji insert dla Robin Hood Hashing
            auto begin_insert_robin_hood = std::chrono::high_resolution_clock::now();
            hash_table_robin_hood.insert({random_value, random_key});
            auto end_insert_robin_hood = std::chrono::high_resolution_clock::now();
            auto elapsed_insert_robin_hood = std::chrono::duration_cast<std::chrono::nanoseconds>(end_insert_robin_hood - begin_insert_robin_hood);
            time_insert_robin_hood += elapsed_insert_robin_hood.count();
            
            // Test operacji remove dla Robin Hood Hashing
            auto begin_remove_robin_hood = std::chrono::high_resolution_clock::now();
            hash_table_robin_hood.remove({random_value, random_key});
            auto end_remove_robin_hood = std::chrono::high_resolution_clock::now();
            auto elapsed_remove_robin_hood = std::chrono::duration_cast<std::chrono::nanoseconds>(end_remove_robin_hood - begin_remove_robin_hood);
            time_remove_robin_hood += elapsed_remove_robin_hood.count();

            // Test operacji insert dla BST Hash Table
            auto begin_insert_BST = std::chrono::high_resolution_clock::now();
            hash_table_BST.insert({random_value, random_key});
            auto end_insert_BST = std::chrono::high_resolution_clock::now();
            auto elapsed_insert_BST = std::chrono::duration_cast<std::chrono::nanoseconds>(end_insert_BST - begin_insert_BST);
            time_insert_BST += elapsed_insert_BST.count();

            // Test operacji remove dla BST Hash Table
            auto begin_remove_BST = std::chrono::high_resolution_clock::now();
            hash_table_BST.remove(random_key);
            auto end_remove_BST = std::chrono::high_resolution_clock::now();
            auto elapsed_remove_BST = std::chrono::duration_cast<std::chrono::nanoseconds>(end_remove_BST - begin_remove_BST);
            time_remove_BST += elapsed_remove_BST.count();

            //std::cout << "przejscie " << i << std::endl;
            // Czyszczenie list
            hash_table_robin_hood.clear();
            hash_table_BST.clear();
        }
        std::cout << "Ilosc elementow " << elemnty << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji insert (Robin Hood Hashing): " << time_insert_robin_hood / ilosc_powtorzen << " ns" << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji remove (Robin Hood Hashing): " << time_remove_robin_hood / ilosc_powtorzen << " ns" << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji insert (BST Hash Table): " << time_insert_BST / ilosc_powtorzen << " ns" << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji remove (BST Hash Table): " << time_remove_BST / ilosc_powtorzen << " ns" << std::endl;
    }

    return 0;
}
