#pragma once
#include "globals.h"

class Project;

class ProjectSerializer {

public:
    static string serialize(const unique_ptr<Project>& project);
    static unique_ptr<Project> deserialize(const string& projectStr);

};
