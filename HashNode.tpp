#include "HashNode.h"

template <typename K, typename V>
HashNode<K, V>::HashNode(K key, V value) : key(key), value(value), occupied(true), deleted(false) {}

template <typename K, typename V>
HashNode<K, V>::HashNode() : occupied(false), deleted(false) {}