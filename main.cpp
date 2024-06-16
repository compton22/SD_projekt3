#include <iostream>
#include "hashTable_openaddressing.h"
#include "hashTable_Cuckoo.h"
#include "hashTable_SeparateChaining.h"

#include "Zapis.h"
#include "test.h"
#include <chrono>
#include <random>

using namespace std;

void testing_hashTable_OA(const unsigned numOfPQ, int size, int iteration, double loadfactor){

    Zapis plik_insert("hashTable_OA_insert.csv");
    Zapis plik_remove("hashTable_OA_remove.csv");

    cout << "Please wait..." << endl;
    //   PriorityQueue *pQ[numOfPQ];
    //   PriorityQueue *pQbackup[numOfPQ];

    // Inicjalizacja tablic wskaźników do tablic mieszających
    hashTable_OA<int, int>** hT_OOA = new hashTable_OA<int, int>*[numOfPQ];

    // Tworzenie numOfPQ tablic mieszających
    for (unsigned i = 0; i < numOfPQ; ++i) {
        hT_OOA[i] = new hashTable_OA<int, int>(size);
    }

    for (int i = 0; i < numOfPQ; i++) {
        hT_OOA[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size*loadfactor);
    }

//    pQ[1]->display();
//    cout << pQ[1]->returnSize() << endl;

    //insert
    double total_time_insert = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size);
        int losowa_liczba = dis(gen);

        auto start = std::chrono::high_resolution_clock::now();
        hT_OOA[i]->insert(losowa_liczba, 5);
        auto end = std::chrono::high_resolution_clock::now();

        total_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    double avg_time_insert = total_time_insert / numOfPQ;
    plik_insert.shot(iteration, avg_time_insert, size, loadfactor);

    //remove
    double total_time_remove = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {

        int key = hT_OOA[i]->getRandomKey();

        auto start = std::chrono::high_resolution_clock::now();
        hT_OOA[i]->remove(key);
        auto end = std::chrono::high_resolution_clock::now();

        total_time_remove += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    double avg_time_remove = total_time_remove / numOfPQ;
    plik_remove.shot(iteration, avg_time_remove, size, loadfactor);

// Powrót do stanu początkowego
    for (int i = 0; i < numOfPQ; i++) {
        delete hT_OOA[i];
    }
    delete[] hT_OOA;

}

void runTests_OA(const unsigned numOfArrays) {

    test::generateRandomNumbers(150000, 0, 100000, "random_numbers.csv", 5);
    test::generateRandomNumbers(150000, 0, 500000, "random_numbers_priority.csv", 3);

    char choice3;
    do {
        cout << "1. array_2k" << endl;
        cout << "2. array_4k" << endl;
        cout << "3. array_6k" << endl;
        cout << "4. array_8k" << endl;
        cout << "5. array_10k" << endl;
        cout << "6. array_12k" << endl;
        cout << "7. array_14k" << endl;
        cout << "8. array_16k" << endl;
        cout << "9. array_18k" << endl;
        cout << "X. array_20k" << endl;
        cout << "A. Test all" << endl;
        cout << "0. Exit" << endl;

        cin >> choice3;
        switch (choice3) {
            case '0':
                cout << "Exiting..." << endl;
                break;
            case '1':
            {
                testing_hashTable_OA(numOfArrays, 1024, 1, 0.3);
                break;
            }
            case '2':
            {
                testing_hashTable_OA(numOfArrays, 4000, 2, 0.3);
                break;
            }
            case '3':
            {
                testing_hashTable_OA(numOfArrays, 6000, 3, 0.3);
                break;
            }
            case '4':
            {
                testing_hashTable_OA(numOfArrays, 8000, 4, 0.3);
                break;
            }
            case '5':
            {
                testing_hashTable_OA(numOfArrays, 10000, 5, 0.3);
                break;
            }
            case '6':
            {
                testing_hashTable_OA(numOfArrays, 12000, 6, 0.3);
                break;
            }
            case '7':
            {
                testing_hashTable_OA(numOfArrays, 14000, 7, 0.3);
                break;
            }
            case '8':
            {
                testing_hashTable_OA(numOfArrays, 16000, 8, 0.3);
                break;
            }
            case '9':
            {
                testing_hashTable_OA(numOfArrays, 18000, 9, 0.3);
                break;
            }
            case 'X':
            {
                testing_hashTable_OA(numOfArrays, 20000, 10, 0.3);
                break;
            }
            case 'A':
            {
                double load_factor[] = {0.01, 0.25, 0.5, 0.75, 0.99};
                for (int i = 0; i < 5; i++) {
                    testing_hashTable_OA(numOfArrays, 1000, 1, load_factor[i]);
                    testing_hashTable_OA(numOfArrays, 2000, 2, load_factor[i]);
                    testing_hashTable_OA(numOfArrays, 4000, 3, load_factor[i]);
                    testing_hashTable_OA(numOfArrays, 8000, 4, load_factor[i]);
                    testing_hashTable_OA(numOfArrays, 16000, 5, load_factor[i]);
                    testing_hashTable_OA(numOfArrays, 32000, 6, load_factor[i]);
                    testing_hashTable_OA(numOfArrays, 64000, 7, load_factor[i]);
                    testing_hashTable_OA(numOfArrays, 120000, 8, load_factor[i]);
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice3 != '0');
}

void testing_hashTable_Cuckoo(const unsigned numOfPQ, int size, int iteration, double loadfactor){

    Zapis plik_insert("hashTable_Cuckoo_insert.csv");
    Zapis plik_remove("hashTable_Cuckoo_remove.csv");

    cout << "Please wait..." << endl;
    //   PriorityQueue *pQ[numOfPQ];
    //   PriorityQueue *pQbackup[numOfPQ];

    // Inicjalizacja tablic wskaźników do tablic mieszających
    hashTable_Cuckoo** hT_Ch = new hashTable_Cuckoo *[numOfPQ];

    // Tworzenie numOfPQ tablic mieszających
    for (unsigned i = 0; i < numOfPQ; ++i) {
        hT_Ch[i] = new hashTable_Cuckoo(size);
    }

    for (int i = 0; i < numOfPQ; i++) {
        hT_Ch[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size*loadfactor);
    }

//    pQ[1]->display();
//    cout << pQ[1]->returnSize() << endl;

    //insert
    double total_time_insert = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size);
        int losowa_liczba = dis(gen);

        auto start = std::chrono::high_resolution_clock::now();
        hT_Ch[i]->insert(losowa_liczba, 5);
        auto end = std::chrono::high_resolution_clock::now();

        total_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    double avg_time_insert = total_time_insert / numOfPQ;
    plik_insert.shot(iteration, avg_time_insert, size, loadfactor);

    //remove
    double total_time_remove = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {

        int key = hT_Ch[i]->getRandomKey();

        auto start = std::chrono::high_resolution_clock::now();
        hT_Ch[i]->remove(key);
        auto end = std::chrono::high_resolution_clock::now();

        total_time_remove += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    double avg_time_remove = total_time_remove / numOfPQ;
    plik_remove.shot(iteration, avg_time_remove, size, loadfactor);

// Powrót do stanu początkowego
    for (int i = 0; i < numOfPQ; i++) {
        delete hT_Ch[i];
    }
    delete[] hT_Ch;
}

void runTests_CH(const unsigned numOfArrays) {

    test::generateRandomNumbers(150000, 0, 100000, "random_numbers.csv", 5);
    test::generateRandomNumbers(150000, 0, 500000, "random_numbers_priority.csv", 3);

    char choice3;
    do {
        cout << "1. array_2k" << endl;
        cout << "2. array_4k" << endl;
        cout << "3. array_6k" << endl;
        cout << "4. array_8k" << endl;
        cout << "5. array_10k" << endl;
        cout << "6. array_12k" << endl;
        cout << "7. array_14k" << endl;
        cout << "8. array_16k" << endl;
        cout << "9. array_18k" << endl;
        cout << "X. array_20k" << endl;
        cout << "A. Test all" << endl;
        cout << "0. Exit" << endl;

        cin >> choice3;
        switch (choice3) {
            case '0':
                cout << "Exiting..." << endl;
                break;
            case '1':
            {
                testing_hashTable_Cuckoo(numOfArrays, 1024, 1, 0.3);
                break;
            }
            case '2':
            {
                testing_hashTable_Cuckoo(numOfArrays, 4000, 2, 0.3);
                break;
            }
            case '3':
            {
                testing_hashTable_Cuckoo(numOfArrays, 6000, 3, 0.3);
                break;
            }
            case '4':
            {
                testing_hashTable_Cuckoo(numOfArrays, 8000, 4, 0.3);
                break;
            }
            case '5':
            {
                testing_hashTable_Cuckoo(numOfArrays, 10000, 5, 0.3);
                break;
            }
            case '6':
            {
                testing_hashTable_Cuckoo(numOfArrays, 12000, 6, 0.3);
                break;
            }
            case '7':
            {
                testing_hashTable_Cuckoo(numOfArrays, 14000, 7, 0.3);
                break;
            }
            case '8':
            {
                testing_hashTable_Cuckoo(numOfArrays, 16000, 8, 0.3);
                break;
            }
            case '9':
            {
                testing_hashTable_Cuckoo(numOfArrays, 18000, 9, 0.3);
                break;
            }
            case 'X':
            {
                testing_hashTable_Cuckoo(numOfArrays, 20000, 10, 0.3);
                break;
            }
            case 'A':
            {
                double load_factor[] = {0.01, 0.25, 0.5, 0.75, 0.99};
                for (int i = 0; i < 5; i++) {
                    testing_hashTable_Cuckoo(numOfArrays, 1000, 1, load_factor[i]);
                    testing_hashTable_Cuckoo(numOfArrays, 2000, 2, load_factor[i]);
                    testing_hashTable_Cuckoo(numOfArrays, 4000, 3, load_factor[i]);
                    testing_hashTable_Cuckoo(numOfArrays, 8000, 4, load_factor[i]);
                    testing_hashTable_Cuckoo(numOfArrays, 16000, 5, load_factor[i]);
                    testing_hashTable_Cuckoo(numOfArrays, 32000, 6, load_factor[i]);
                    testing_hashTable_Cuckoo(numOfArrays, 64000, 7, load_factor[i]);
                    testing_hashTable_Cuckoo(numOfArrays, 120000, 8, load_factor[i]);
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice3 != '0');
}


void testing_hashTable_Separate(const unsigned numOfPQ, int size, int iteration, double loadfactor){

    Zapis plik_insert("hashTable_Separate_insert.csv");
    Zapis plik_remove("hashTable_Separate_remove.csv");

    cout << "Please wait..." << endl;
    //   PriorityQueue *pQ[numOfPQ];
    //   PriorityQueue *pQbackup[numOfPQ];

    // Inicjalizacja tablic wskaźników do tablic mieszających
    hashTable_SeparateChaining** hT_SC = new hashTable_SeparateChaining *[numOfPQ];

    // Tworzenie numOfPQ tablic mieszających
    for (unsigned i = 0; i < numOfPQ; ++i) {
        hT_SC[i] = new hashTable_SeparateChaining(size);
    }

    for (int i = 0; i < numOfPQ; i++) {
        hT_SC[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size*loadfactor);
    }

//    pQ[1]->display();
//    cout << pQ[1]->returnSize() << endl;

    //insert
    double total_time_insert = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size);
        int losowa_liczba = dis(gen);

        auto start = std::chrono::high_resolution_clock::now();
        hT_SC[i]->insert(losowa_liczba, 5);
        auto end = std::chrono::high_resolution_clock::now();

        total_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    double avg_time_insert = total_time_insert / numOfPQ;
    plik_insert.shot(iteration, avg_time_insert, size, loadfactor);

    //remove
    double total_time_remove = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {

        int key = hT_SC[i]->getRandomKey();

        auto start = std::chrono::high_resolution_clock::now();
        hT_SC[i]->remove(key);
        auto end = std::chrono::high_resolution_clock::now();

        total_time_remove += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    double avg_time_remove = total_time_remove / numOfPQ;
    plik_remove.shot(iteration, avg_time_remove, size, loadfactor);

// Powrót do stanu początkowego
    for (int i = 0; i < numOfPQ; i++) {
        delete hT_SC[i];
    }
    delete[] hT_SC;
}

void runTests_SC(const unsigned numOfArrays) {

    test::generateRandomNumbers(150000, 0, 100000, "random_numbers.csv", 5);
    test::generateRandomNumbers(150000, 0, 500000, "random_numbers_priority.csv", 3);

    char choice3;
    do {
        cout << "1. array_2k" << endl;
        cout << "2. array_4k" << endl;
        cout << "3. array_6k" << endl;
        cout << "4. array_8k" << endl;
        cout << "5. array_10k" << endl;
        cout << "6. array_12k" << endl;
        cout << "7. array_14k" << endl;
        cout << "8. array_16k" << endl;
        cout << "9. array_18k" << endl;
        cout << "X. array_20k" << endl;
        cout << "A. Test all" << endl;
        cout << "0. Exit" << endl;

        cin >> choice3;
        switch (choice3) {
            case '0':
                cout << "Exiting..." << endl;
                break;
            case '1':
            {
                testing_hashTable_Separate(numOfArrays, 1024, 1, 0.3);
                break;
            }
            case '2':
            {
                testing_hashTable_Separate(numOfArrays, 4000, 2, 0.3);
                break;
            }
            case '3':
            {
                testing_hashTable_Separate(numOfArrays, 6000, 3, 0.3);
                break;
            }
            case '4':
            {
                testing_hashTable_Separate(numOfArrays, 8000, 4, 0.3);
                break;
            }
            case '5':
            {
                testing_hashTable_Separate(numOfArrays, 10000, 5, 0.3);
                break;
            }
            case '6':
            {
                testing_hashTable_Separate(numOfArrays, 12000, 6, 0.3);
                break;
            }
            case '7':
            {
                testing_hashTable_Separate(numOfArrays, 14000, 7, 0.3);
                break;
            }
            case '8':
            {
                testing_hashTable_Separate(numOfArrays, 16000, 8, 0.3);
                break;
            }
            case '9':
            {
                testing_hashTable_Separate(numOfArrays, 18000, 9, 0.3);
                break;
            }
            case 'X':
            {
                testing_hashTable_Separate(numOfArrays, 20000, 10, 0.3);
                break;
            }
            case 'A':
            {
                double load_factor[] = {0.01, 0.25, 0.5, 0.75, 0.99};
                for (int i = 0; i < 5; i++) {
                    testing_hashTable_Separate(numOfArrays, 1000, 1, load_factor[i]);
                    testing_hashTable_Separate(numOfArrays, 2000, 2, load_factor[i]);
                    testing_hashTable_Separate(numOfArrays, 4000, 3, load_factor[i]);
                    testing_hashTable_Separate(numOfArrays, 8000, 4, load_factor[i]);
                    testing_hashTable_Separate(numOfArrays, 16000, 5, load_factor[i]);
                    testing_hashTable_Separate(numOfArrays, 32000, 6, load_factor[i]);
                    testing_hashTable_Separate(numOfArrays, 64000, 7, load_factor[i]);
                    testing_hashTable_Separate(numOfArrays, 120000, 8, load_factor[i]);
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice3 != '0');
}

int main() {
    char choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Tests Open Addressing" << endl;
        cout << "2. Tests Cuckoo Hashing" << endl;
        cout << "3. Tests Separate Chaining" << endl;
        cout << "4. small test" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: " << endl;
        cin >> choice;

        switch(choice) {
            case '1':
                cout << "Running tests open addressing..." << endl;
                cout << "Please choose the number of hash tables with open addressing, " << endl;
                int numOfArrays;
                cin >> numOfArrays;
                cout << "Please wait..." << endl;
                runTests_OA(numOfArrays);
                break;
            case '2':
                cout << "Running tests cuckoo hashing..." << endl;
                cout << "Please choose the number of hash tables with cuckoo hashing, " << endl;
                int numOfArrays1;
                cin >> numOfArrays1;
                cout << "Please wait..." << endl;
                runTests_CH(numOfArrays1);
                break;
            case '3':
                cout << "Running tests separate chaining..." << endl;
                cout << "Please choose the number of hash tables with separate chaining, " << endl;
                int numOfArrays2;
                cin >> numOfArrays2;
                cout << "Please wait..." << endl;
                runTests_SC(numOfArrays2);
                break;
            case '4': {
                cout << "Running small test open addressing..." << endl;
                hashTable_OA<int, int> hT_OA(20);
                hT_OA.insert(1, 5);
                hT_OA.insert(2, 10);
                hT_OA.display();
                cout << "Running small test cuckoo hashing..." << endl;
                hashTable_Cuckoo hT_CH(20);
                hT_CH.insert(1, 5);
//                cout << "dzialaam" << endl;
                hT_CH.insert(2, 10);
                hT_CH.display();
                break;
                }
            case '5':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != '3');

    return 0;
}