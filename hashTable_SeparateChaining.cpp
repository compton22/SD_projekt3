#include "hashTable_SeparateChaining.h"
#include <fstream>
#include <iostream>

hashTable_SeparateChaining::hashTable_SeparateChaining(int size) : size(0), capacity(size) {
    table = new BST[size];
}

hashTable_SeparateChaining::~hashTable_SeparateChaining() {
    delete[] table;
}

int hashTable_SeparateChaining::hash(int key) {
    return key % capacity;
}

void hashTable_SeparateChaining::insert(int key, int val) {
    int index = hash(key);
    table[index].insert(key, val);
    size++;
}

void hashTable_SeparateChaining::remove(int key) {
    int index = hash(key);
    table[index].remove(key);
    size--;
}

int hashTable_SeparateChaining::getRandomKey() {
    if (size == 0) {
        // Tablica jest pusta, nie można zwrócić losowego klucza
        return -1;
    }

    int index;
    do {
        index = rand() % capacity;
    } while (table[index].isEmpty());

    return table[index].getRandomKeyBST();
}

void hashTable_SeparateChaining::fillFromCSV(const std::string& value_file_name, const std::string& key_file_name, int n) {
    std::ifstream value_file(value_file_name);
    std::ifstream key_file(key_file_name);

    if (!value_file.is_open() || !key_file.is_open()){
        std::cerr << "Error: File not found." << std::endl;
        return;
    }

    for (int i = 0; i < n; i++){
        int key, val;
        key_file >> key;
        value_file >> val;
        insert(key, val);
    }

    value_file.close();
    key_file.close();
}