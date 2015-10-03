#include "project_serializer.h"

#include <sstream>

#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

#include "project.h"
#include "project_class_serializer.h"

string ProjectSerializer::serialize(const unique_ptr<Project>& project)
{
    std::stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(project);
    } // oarchive needs to go out of scope in order to flush its contents
    return ss.str();
}

unique_ptr<Project> ProjectSerializer::deserialize(const string& projectStr)
{
    std::stringstream ss{projectStr};
    cereal::JSONInputArchive iarchive(ss);
    unique_ptr<Project> project;
    iarchive(project);
    return move(project);
}
