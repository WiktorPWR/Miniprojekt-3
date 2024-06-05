#include <iostream>
#include "RobinHood_hashing.cpp"
#include "string"
#include "Hash_table_with_BST.cpp"
#include "Hash_table_chain.cpp"
#include <cstdlib>
#include <chrono>

int main() {
    srand((unsigned) time(NULL));
    RobinHoodHashing<int> hash_table_robin_hood;
    Hash_table_BST<int> hash_table_BST;
    Chain_hash<int, int> hash_chain;


    const int ilosc_powtorzen = 100;
    int ilosc_elemtow[] = {5000, 8000, 10000, 16000, 20000, 40000, 60000};
    double time_insert_robin_hood = 0;
    double time_insert_chain = 0;
    double time_remove_robin_hood = 0;
    double time_remove_chain = 0;
    double time_insert_BST = 0;
    double time_remove_BST = 0;

    for (int elemnty : ilosc_elemtow) {
        for (int i = 0; i <= ilosc_powtorzen; i++) {
            //std::cout << "dupa";
            // Utworzenie tablicy elementów
            for (int j = 0; j <= elemnty; j++) {
                int random_value = rand();
                int random_key = rand();
                //hash_table_robin_hood.insert({random_value, random_key});
                //hash_table_BST.insert({random_value, random_key});

                hash_chain.addElement(random_key,random_value);
                // std::cout << "Dodanie elementu " << j << std::endl;
            }
            
            // Testy
            int random_value = rand();
            int random_key = rand();
/*
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
*/
            // Test operacji insert dla Robin Hood Hashing
            auto begin_insert_chain = std::chrono::high_resolution_clock::now();
            hash_chain.addElement(random_value, random_key);
            auto end_insert_chain = std::chrono::high_resolution_clock::now();
            auto elapsed_insert_chain = std::chrono::duration_cast<std::chrono::nanoseconds>(end_insert_chain - begin_insert_chain);
            time_insert_chain += elapsed_insert_chain.count();

            // Test operacji remove dla Robin Hood Hashing
            auto begin_remove_chain = std::chrono::high_resolution_clock::now();
            hash_chain.removeElement(random_key );
            auto end_remove_chain = std::chrono::high_resolution_clock::now();
            auto elapsed_remove_chain = std::chrono::duration_cast<std::chrono::nanoseconds>(end_remove_chain - begin_remove_chain);
            time_remove_chain += elapsed_remove_chain.count();

            //std::cout << "przejscie " << i << std::endl;
            // Czyszczenie list
            //hash_table_robin_hood.clear();
            //hash_table_BST.clear();
            hash_chain.clear();

        }
        std::cout << "Ilosc elementow: " << elemnty << std::endl;
        /*std::cout << "Czas wykonania pojedynczej operacji insert (Robin Hood Hashing): " << time_insert_robin_hood / ilosc_powtorzen << " ns" << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji remove (Robin Hood Hashing): " << time_remove_robin_hood / ilosc_powtorzen << " ns" << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji insert (BST Hash Table): " << time_insert_BST / ilosc_powtorzen << " ns" << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji remove (BST Hash Table): " << time_remove_BST / ilosc_powtorzen << " ns" << std::endl;
        */std::cout << "Czas wykonania pojedynczej operacji insert (Chain Hash Table): " << time_insert_chain / ilosc_powtorzen << " ns" << std::endl;
        std::cout << "Czas wykonania pojedynczej operacji remove (Chain Hash Table): " << time_remove_chain / ilosc_powtorzen << " ns" << std::endl;
    }

    return 0;
}
