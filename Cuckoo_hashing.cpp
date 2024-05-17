#include <iostream>

template <typename T> class Cuckoo_hashing {
private:
    struct Node {
        T value;
        int key;
    };

    int array_size = 10;
    int elements = 0;
    Node* array_1;
    Node* array_2;

    int hash1(int key) {
        return key % array_size;
    }

    int hash2(int key) {
        return (key / array_size) % array_size;
    }

    void rehash() {
        int old_size = array_size;
        array_size *= 2;

        Node* newlist_1 = new Node[array_size];
        Node* newlist_2 = new Node[array_size];
        Node* buffer = new Node[elements+1];

        int iterator = 0;
        for (int i = 0; i < old_size; i++) {
            if (array_1[i].key != -1) {
                buffer[iterator++] = array_1[i];
            }
            if (array_2[i].key != -1) {
                buffer[iterator++] = array_2[i];
            }
        }

        delete[] array_1;
        delete[] array_2;
        array_1 = newlist_1;
        array_2 = newlist_2;

        for (int j = 0; j < elements; j++) {
            insert(buffer[j]);
        }

        delete[] buffer;
    }

public:
    Cuckoo_hashing() {
        array_1 = new Node[array_size];
        array_2 = new Node[array_size];
    }

    ~Cuckoo_hashing() {
        delete[] array_1;
        delete[] array_2;
    }

    void insert(Node node) {
        int count = 0;
        int max_iterations = array_size * 2;

        while (count < max_iterations) {
            int pos1 = hash1(node.key);

            if (array_1[pos1].key == -1) {
                array_1[pos1] = node;
                elements++;
                return;
            }

            Node temp_1 = array_1[pos1];
            array_1[pos1] = node;
            int pos2 = hash2(node.key);

            if (array_2[pos2].key == -1) {
                array_2[pos2] = temp_1;
                elements++;
                return;
            }

            node = array_2[pos2];
            array_2[pos2] = temp_1;
            count++;
        }

        rehash();
        insert(node);
    }
};

int main() {
    Cuckoo_hashing<int> hash_table;
    // Do something with hash_table
    return 0;
}
