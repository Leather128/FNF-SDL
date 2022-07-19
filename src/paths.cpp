#include <unistd.h>
#include <limits.h>
#include <string>
#include <libgen.h>

#include "paths.h"

std::string Paths::cwd;

void Paths::init()
{
    char temp[PATH_MAX];

    ssize_t count = readlink("/proc/self/exe", temp, PATH_MAX);

    if (count != -1)
        Paths::cwd = std::string(dirname(temp));
}

std::string Paths::get_system_path(std::string local_path)
{
    return Paths::cwd + "/" + local_path;
}