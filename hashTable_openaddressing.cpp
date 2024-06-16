#include "hashTable_openaddressing.h"
#include <iostream>
#include <fstream>
#include <ctime>

// Implementacja klasy hashTable_OA
template <typename K, typename V>
hashTable_OA<K, V>::hashTable_OA(int capacity) : capacity(capacity), size(0) {
    table = new HashNode<K, V>[capacity];
}

template <typename K, typename V>
hashTable_OA<K, V>::~hashTable_OA() {
    delete[] table;
}

template <typename K, typename V>
int hashTable_OA<K, V>::hashFunction(K key) {
    return key % capacity;
}

template <typename K, typename V>
int hashTable_OA<K, V>::linearProbe(int index, K key) {
    int i = 0;
    while (table[(index + i) % capacity].occupied &&
           !table[(index + i) % capacity].deleted &&
           table[(index + i) % capacity].key != key) {
        ++i;
    }
    return (index + i) % capacity;
}

template <typename K, typename V>
int hashTable_OA<K, V>::insert(K key, V value) {
    int hashIndex = hashFunction(key);
    int newIndex = -1;

    while (table[hashIndex].occupied &&
           table[hashIndex].key != key &&
           !table[hashIndex].deleted) {
        hashIndex++;
        hashIndex %= capacity;
    }

    if (!table[hashIndex].occupied || table[hashIndex].deleted) {
        table[hashIndex] = HashNode<K, V>(key, value);
        ++size;
    } else if (table[hashIndex].key == key) {
        newIndex = linearProbe(hashIndex, key);
        table[newIndex] = HashNode<K, V>(key, value);
        ++size;
    }
}

template <typename K, typename V>
int hashTable_OA<K, V>::remove(K key) {
    int index = hashFunction(key);
    index = linearProbe(index, key);

    if (index < capacity && table[index].occupied && !table[index].deleted &&
        table[index].key == key) {
        table[index].occupied = false;
        table[index].deleted = true;
        --size;
        return index;
    } else {
        std::cerr << "Error: Removal failed. Key not found." << std::endl;
        return -1;
    }
}

template <typename K, typename V>
void hashTable_OA<K, V>::display() {
    for (int i = 0; i < capacity; i++) {
        if (table[i].occupied && !table[i].deleted) {
            std::cout << "Key: " << table[i].key << ", Value: " << table[i].value << std::endl;
        }
    }
}

template <typename K, typename V>
void hashTable_OA<K, V>::fillFromCSV(const std::string& value_file_name, const std::string& key_file_name, int n) {
    std::ifstream valueFile(value_file_name);
    std::ifstream keyFile(key_file_name);

    if (!valueFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku wartości do odczytu." << std::endl;
        return;
    }

    if (!keyFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku kluczy do odczytu." << std::endl;
        return;
    }

    std::string valueLine;
    std::string keyLine;

    for (int i = 0; i < n; ++i) {
        if (std::getline(valueFile, valueLine) && std::getline(keyFile, keyLine)) {
            int value = std::stoi(valueLine);
            int key = std::stoi(keyLine);

            insert(key, value);
        } else {
            std::cerr << "Wystąpił błąd podczas odczytu danych." << std::endl;
            break;
        }
    }

    valueFile.close();
    keyFile.close();
}

template <typename K, typename V>
K hashTable_OA<K, V>::getRandomKey() {
    std::srand(std::time(0));
    while (true) {
        int randomIndex = std::rand() % capacity;
        if (table[randomIndex].occupied && !table[randomIndex].deleted) {
            return table[randomIndex].key;
        }
    }
}
