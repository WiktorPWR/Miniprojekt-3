#include "C:\Users\WiktorJankowski-Ostr\Miniprojekt-3\dynamic_array.cpp"
#include <iostream>

template <typename T> class Cuckoo_hashing
{
    private:
        //tutaj funckje haszujace
        //oraz no wiaodmo zmienne 
        struct node
        {
            T value;
            int key;
        };
        DynamicArray array_1;
        DynamicArray array_2;

        int hash1(int key, int table_size) 
        {
            return key % table_size;
        }

        int hash2(int key, int table_size) 
        {
            return (key / table_size) % table_size;
        }

        
    public:
        //implementacja metod insert() oraz remove() przydalo by sie jeszcze jakie print moze zeby sprawdziczy dziala
        //metoda rehash
    

        void insert(value,key)
        {

        }

};
