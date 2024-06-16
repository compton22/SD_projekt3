#include "test.h"
#include <iostream>
#include <fstream>
#include <random>

void test::generateRandomNumbers(int numNumbers, int minValue, int maxValue, const std::string& filename, int seed) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int> distribution(minValue, maxValue);


    for (int i = 0; i < numNumbers; ++i) {
        int randomNumber = distribution(generator);
        outputFile << randomNumber << std::endl;
    }

    if(outputFile.is_open()) outputFile.close();
}