#include "file_utils.h"

#include <sys/stat.h>

// See: http://stackoverflow.com/a/12774387/216311
bool file_exists(const std::string& name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}