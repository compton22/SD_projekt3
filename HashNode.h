#ifndef SD_PROJEKT3_HASHNODE_H
#define SD_PROJEKT3_HASHNODE_H

template <typename K, typename V>
class HashNode {
public:
    V value;
    K key;
    bool occupied;
    bool deleted;

    HashNode(K key, V value);
    HashNode();
};

#include "HashNode.tpp"


#endif //SD_PROJEKT3_HASHNODE_H
