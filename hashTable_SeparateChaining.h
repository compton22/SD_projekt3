#ifndef SD_PROJEKT3_HASHTABLE_SEPARATECHAINING_H
#define SD_PROJEKT3_HASHTABLE_SEPARATECHAINING_H

#include <string>
#include "BST.h"

class hashTable_SeparateChaining : public BST {
    int size;
    int capacity;
    BST *table;
public:
    hashTable_SeparateChaining(int size);
    ~hashTable_SeparateChaining();
    int hash(int key);
    void insert(int key, int val);
    void remove(int key);
    int getRandomKey();
    void fillFromCSV(const std::string &value_file_name, const std::string &key_file_name, int n);
};


#endif //SD_PROJEKT3_HASHTABLE_SEPARATECHAINING_H
