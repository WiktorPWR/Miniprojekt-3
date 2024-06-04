#include <iostream>
#include <stdexcept>

template<typename T>
class AVLTree {
private:
    struct AVLNode {
        T value;
        int key;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const T& val, int k) : value(val), key(k), left(nullptr), right(nullptr), height(1) {}
    };

    AVLNode* root;

    int height(AVLNode* node) const {
        return node ? node->height : 0;
    }

    int balance_factor(AVLNode* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void update_height(AVLNode* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    AVLNode* rotate_right(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        update_height(y);
        update_height(x);

        return x;
    }

    AVLNode* rotate_left(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        update_height(x);
        update_height(y);

        return y;
    }

    AVLNode* balance(AVLNode* node) {
        update_height(node);
        int balance = balance_factor(node);

        if (balance > 1) {
            if (balance_factor(node->left) < 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        if (balance < -1) {
            if (balance_factor(node->right) > 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, const T& value, int key) {
        if (!node) return new AVLNode(value, key);

        if (key < node->key) {
            node->left = insert(node->left, value, key);
        } else if (key > node->key) {
            node->right = insert(node->right, value, key);
        } else {
            node->value = value;
            return node;
        }

        return balance(node);
    }

    AVLNode* min_value_node(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    AVLNode* remove(AVLNode* root, int key) {
        if (!root) return root;

        if (key < root->key) {
            root->left = remove(root->left, key);
        } else if (key > root->key) {
            root->right = remove(root->right, key);
        } else {
            if (!root->left || !root->right) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = min_value_node(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = remove(root->right, temp->key);
            }
        }

        if (!root) return root;

        return balance(root);
    }

    AVLNode* search(AVLNode* root, int key) const {
        if (!root || root->key == key) return root;

        if (key < root->key) return search(root->left, key);

        return search(root->right, key);
    }

    void clear(AVLNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void print(AVLNode* node) const {
        if (node) {
            print(node->left);
            std::cout << "(" << node->key << ", " << node->value << ") ";
            print(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(const T& value, int key) {
        root = insert(root, value, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    bool contains(int key) const {
        return search(root, key) != nullptr;
    }

    T get(int key) const {
        AVLNode* node = search(root, key);
        if (!node) throw std::out_of_range("Key not found");
        return node->value;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    void print() const {
        print(root);
    }
};

template <typename T>
class Hash_table_BST {
public:
    struct Node {
        T value;
        int key;
        Node() : key(-1) {} // Default constructor setting default values
        Node(T val, int k) : value(val), key(k) {} // Constructor with parameters initializing fields

        bool operator<(const Node& other) const {
            return key < other.key;
        }

        friend std::ostream& operator<<(std::ostream& os, const Node& node) {
            os << "(" << node.key << ", " << node.value << ")";
            return os;
        }
    };

private:
    int array_size;
    int elements;
    AVLTree<Node>* array;

    int hash(int key) const {
        unsigned int ukey = static_cast<unsigned int>(key);
        ukey = (ukey ^ 0xdeadbeef) + (ukey << 4) + 0x42;
        return static_cast<int>(ukey % static_cast<unsigned int>(array_size));
    }

    void resize(int new_size) {
        AVLTree<Node>* new_array = new AVLTree<Node>[new_size];
        for (int i = 0; i < array_size; ++i) {
            while (array[i].contains(array[i].get(i).key)) {
                Node node = array[i].get(i);
                int index = hash(node.key);
                new_array[index].insert(node, node.key);
            }
        }
        delete[] array;
        array = new_array;
        array_size = new_size;
    }

    void check_load_factor_and_resize() {
        if (elements >= array_size * 0.75) { // resize if load factor exceeds 0.75
            resize(array_size * 2);
        }
    }

public:
    Hash_table_BST(int size = 2000) : array_size(size), elements(0) {
        array = new AVLTree<Node>[array_size];
    }

    ~Hash_table_BST() {
        delete[] array;
    }

    void insert(const Node& node) {
        check_load_factor_and_resize();
        int index = hash(node.key);
        array[index].insert(node, node.key);
        ++elements;
    }

    void remove(int key) {
        int index = hash(key);
        if (!array[index].contains(key)) {
            throw std::out_of_range("Key not found");
        }
        array[index].remove(key);
        --elements;
    }

    void clear() {
        delete[] array;
        array = new AVLTree<Node>[array_size];
        elements = 0;
    }

    void print() const {
        for (int i = 0; i < array_size; ++i) {
            std::cout << "Bucket " << i << ": ";
            array[i].print();
            std::cout << std::endl;
        }
    }
};


