#ifndef SD_PROJEKT3_BST_H
#define SD_PROJEKT3_BST_H

#include <iostream>

class Node{
public:
    int key;
    int val;
    Node* left;
    Node* right;

    Node(int key, int val){
        this->key = key;
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
    Node* root;

    Node* insertionHelper(Node* root, Node* node);
    Node* removeHelper(Node* root, int key);
    void printHelper(Node* root);
    Node* successor(Node* root);
    Node* predecessor(Node* root);
    Node* getHelper(Node* root, int key);
public:
    BST();
    ~BST();
    void insert(int key, int val);
    void remove(int key);
    void display();
    bool isEmpty();
    int get(int key);
    int getRandomKeyBST();
};

#endif //SD_PROJEKT3_BST_H
