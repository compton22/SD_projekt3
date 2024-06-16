#ifndef SD_PROJEKT3_HASHTABLE_OPENADDRESSING_H
#define SD_PROJEKT3_HASHTABLE_OPENADDRESSING_H

#include <string>
#include "HashNode.h"

template <typename K, typename V>
class hashTable_OA {
private:
    HashNode<K, V>* table;
    int capacity;
    int size;

    int hashFunction(K key);
    int linearProbe(int index, K key);

public:
    hashTable_OA(int capacity);
    ~hashTable_OA();

    int insert(K key, V value);
    int remove(K key);
    void display();
    void fillFromCSV(const std::string& value_file_name, const std::string& key_file_name, int n);
    K getRandomKey();
};

#include "hashTable_openaddressing.cpp"

#endif //SD_PROJEKT3_HASHTABLE_OPENADDRESSING_H
