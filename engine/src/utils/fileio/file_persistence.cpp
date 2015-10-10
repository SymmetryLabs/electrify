#include "file_persistence.h"

#include <fstream>

std::string FilePersistence::readFromFile(const std::string& filename)
{
    std::string str;
    std::ifstream file(filename);

    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        str.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        str.assign(std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>());

        file.close();
    }
    return str;
}

bool FilePersistence::writeToFile(const std::string& str, const std::string& filename)
{

    std::ofstream file(filename);
    if (file.is_open()) {
        file << str;
        file.close();
        return true;
    }
    return false;
}
