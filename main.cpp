#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr << "Invalid number of arguments!" << '\n';
        return -1;
    }
    return 0;
}