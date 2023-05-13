#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>

namespace fileHandling
{
    
class FileHandler
{
public:
    void WriteToFile(std::string pack);
private:
    std::filesystem::path m_path = "passwords.txt";
};

}