#include "hashTable_Cuckoo.h"
#include "HashNode.h"

hashTable_Cuckoo::hashTable_Cuckoo(int capacity) : capacity(capacity), size(0) {
    table1 = new HashNode<int, int>[capacity/2];
    table2 = new HashNode<int, int>[capacity/2];
}

hashTable_Cuckoo::~hashTable_Cuckoo() {
    delete[] table1;
    delete[] table2;
}

int hashTable_Cuckoo::hashFunction1(int key) {
    return key % (capacity / 2);
}

int hashTable_Cuckoo::hashFunction2(int key) {
    return (key / (capacity / 2)) % (capacity / 2);
}

void hashTable_Cuckoo::insert(int key, int value) {
    HashNode<int, int> node(key, value);
    for (int cycles = 0; cycles < maxCycle; cycles++){
        //std::cout << "okeej" << std::endl;
        int index1 = hashFunction1(node.key);
        if (!table1[index1].occupied){
            table1[index1] = node;
            size++;
            return;
        }
        HashNode<int, int> temp = table1[index1];
        table1[index1] = node;
        node = temp;

        int index2 = hashFunction2(node.key);
        if (!table2[index2].occupied){
            table2[index2] = node;
            size++;
            return;
        }
        HashNode<int, int> temp2 = table2[index2];
        table2[index2] = node;
        node = temp2;
    }
    //resize();
}

void hashTable_Cuckoo::resize() {
    HashNode<int, int>* oldTable1 = table1;
    HashNode<int, int>* oldTable2 = table2;
    int oldCapacity = capacity;
    capacity = capacity * 2;

    table1 = new HashNode<int, int>[capacity/2];
    table2 = new HashNode<int, int>[capacity/2];
    size = 0;

    for (int i = 0; i < capacity/4; i++){
        if (oldTable1[i].occupied){
            insert(oldTable1[i].key, oldTable1[i].value);
        }
        if (oldTable2[i].occupied){
            insert(oldTable2[i].key, oldTable2[i].value);
        }
    }

    delete[] oldTable1;
    delete[] oldTable2;
}

void hashTable_Cuckoo::remove(int key) {
    int index1 = hashFunction1(key);
    if (table1[index1].occupied && table1[index1].key == key){
        table1[index1].occupied = false;
        size--;
        return;
    }
    int index2 = hashFunction2(key);
    if (table2[index2].occupied && table2[index2].key == key){
        table2[index2].occupied = false;
        size--;
        return;
    }
}

void hashTable_Cuckoo::display() {
    for (int i = 0; i < capacity/2; i++){
        if (table1[i].occupied){
            std::cout << "table1[" << i << "] = " << table1[i].key << " " << table1[i].value << std::endl;
        }
        if (table2[i].occupied){
            std::cout << "table2[" << i << "] = " << table2[i].key << " " << table2[i].value << std::endl;
        }
    }
}

void hashTable_Cuckoo::fillFromCSV(const std::string& value_file_name, const std::string& key_file_name, int n) {
    std::ifstream value_file(value_file_name);
    std::ifstream key_file(key_file_name);

    if (!value_file.is_open() || !key_file.is_open()){
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    for (int i = 0; i < n; i++){
        int key, value;
        value_file >> value;
        key_file >> key;
        insert(key, value);
    }

    value_file.close();
    key_file.close();
}

int hashTable_Cuckoo::getRandomKey() {
    std::srand(std::time(0));
    while (true) {
        // Losuj tablicę (0 dla table1, 1 dla table2)
        int tableNumber = std::rand() % 2;
        // Losuj indeks w wybranej tablicy
        int randomIndex = std::rand() % (capacity / 2);

        if (tableNumber == 0 && table1[randomIndex].occupied && !table1[randomIndex].deleted) {
            return table1[randomIndex].key;
        }

        if (tableNumber == 1 && table2[randomIndex].occupied && !table2[randomIndex].deleted) {
            return table2[randomIndex].key;
        }
    }
}