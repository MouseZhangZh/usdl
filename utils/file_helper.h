//
// Created by Mouse Zhang on 2024/1/6.
//

#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <string>
#include <fstream>

class FileHelper {
public:
    static std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }

    static void writeFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        file << content;
    }
};


#endif //FILE_HELPER_H
