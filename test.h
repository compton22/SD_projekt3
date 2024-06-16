#ifndef SD_PROJEKT3_TEST_H
#define SD_PROJEKT3_TEST_H

#include <string>
#include <chrono>

class test {
public:
    static void generateRandomNumbers(int numNumbers, int minValue, int maxValue, const std::string& filename, int seed);
};

#endif //SD_PROJEKT3_TEST_H
