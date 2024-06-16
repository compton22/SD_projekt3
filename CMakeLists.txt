cmake_minimum_required(VERSION 3.23)
project(SD_projekt3)

set(CMAKE_CXX_STANDARD 20)

add_executable(SD_projekt3 main.cpp hashTable_openaddressing.h Zapis.cpp Zapis.h test.cpp test.h HashNode.tpp HashNode.h hashTable_Cuckoo.cpp hashTable_Cuckoo.h hashTable_SeparateChaining.cpp hashTable_SeparateChaining.h BST.cpp BST.h)
