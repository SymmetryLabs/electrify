#pragma once

#include <string>

class FilePersistence {

public:
    static std::string readFromFile(const std::string& filename);
    static bool writeToFile(const std::string& str, const std::string& filename);

};
