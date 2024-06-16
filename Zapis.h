#ifndef SD_PROJEKT3_ZAPIS_H
#define SD_PROJEKT3_ZAPIS_H

#include <fstream>
#include <string>

class Zapis {
public:
    // Konstruktor przyjmuj¹cy nazwê pliku
    Zapis(const std::string& filename);

    // Metoda do zapisu danych do pliku CSV
    void shot(int iteration, unsigned duration, int size, double loadFactor);

private:
    std::string filename; // Nazwa pliku
    std::ofstream file;
};

#endif //SD_PROJEKT3_ZAPIS_H
