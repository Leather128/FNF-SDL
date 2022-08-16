#pragma once

#include <string>

class Paths
{
public:
    static std::string cwd;

    static void init();

    static std::string get_system_path(std::string local_path);
};