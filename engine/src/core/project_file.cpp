#include "project_file.h"

#include "project.h"
#include "project_serializer.h"
#include "file_persistence.h"

ProjectFile::ProjectFile(const string& filename_)
: filename(filename_)
{
}

unique_ptr<Project> ProjectFile::loadFromFile() const
{
    auto str = FilePersistence::readFromFile(filename);
    return ProjectSerializer::deserialize(str);
}

bool ProjectFile::saveToFile(const unique_ptr<Project>& project) const
{
    auto str = ProjectSerializer::serialize(project);
    return FilePersistence::writeToFile(str, filename);
}
