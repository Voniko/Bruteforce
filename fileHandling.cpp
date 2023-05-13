#include "fileHandling.h"

void fileHandling::FileHandler::WriteToFile(std::string pack)    //Writing passwords to file
{
    std::ofstream file(m_path, std::ios::app);
    if (file.is_open()) {

        file << pack << '\n';
    }
    file.close();
}