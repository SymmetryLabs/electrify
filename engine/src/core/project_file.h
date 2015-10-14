#pragma once
#include "globals.h"

class Project;

class ProjectFile {

public:
    explicit ProjectFile(const string& filename);

    unique_ptr<Project> loadFromFile() const;
    bool saveToFile(const unique_ptr<Project>& project) const;

    template <typename T>
    unique_ptr<T> loadFromFile() const;

private:
    string filename;

};

#include "project_file.hpp"
