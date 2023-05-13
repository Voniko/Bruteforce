#pragma once

#include "fileHandling.h"
#include <string>
#include <cmath>
#include <windows.h>
#include <thread>
#include <mutex>

namespace bruteforce
{

class Bruteforce
{
public:
    void Start();
    void SetPassword(std::string pass) { m_pass = pass; };
    std::string GetPassword() const { return m_pass; };
private:
    void BruteForce(int start, int end);
    int AmountPassword();
    std::string GeneratePassword(uint64_t index);
private:
    std::string m_availableSymbol = "abcdefghijklmnopqrstuvwxyz0123456789";
    std::atomic_flag m_passwordNotFound = ATOMIC_FLAG_INIT;
    int m_length = 4;
    std::mutex m_fileMutex;
    std::string m_pass;
};

}