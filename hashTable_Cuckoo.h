#ifndef SD_PROJEKT3_HASHTABLE_CUCKOO_H
#define SD_PROJEKT3_HASHTABLE_CUCKOO_H

#include "HashNode.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class hashTable_Cuckoo {
private:
    int size;
    int capacity;
    int maxCycle = 1000;

    HashNode<int, int>* table1;
    HashNode<int, int>* table2;
public:
    hashTable_Cuckoo(int capacity);
    ~hashTable_Cuckoo();

    int hashFunction1(int key);
    int hashFunction2(int key);
    void insert(int key, int value);
    void remove(int key);
    void resize();
    void display();
    void fillFromCSV(const std::string& value_file_name, const std::string& key_file_name, int n);
    int getRandomKey();
};


#endif //SD_PROJEKT3_HASHTABLE_CUCKOO_H
