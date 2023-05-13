#include "Bruteforce.h"

void bruteforce::Bruteforce::Start()   //Calculate number of passwords for each thread , create thread
{
    std::vector<std::jthread> threads;
    int step = std::ceil(static_cast<double>(AmountPassword()) / std::jthread::hardware_concurrency());;
    int start = 0;
    int end = 0;
    for (int i = 0; i < std::jthread::hardware_concurrency(); ++i)
    {
        start = end;
        end += step;
        if (end > AmountPassword())
        {
            end = AmountPassword();
        }

        threads.push_back(std::jthread(&Bruteforce::BruteForce, this, start, end));
    }
    for (auto &thread : threads)
    {
        thread.join();
    }
}

void bruteforce::Bruteforce::BruteForce(int start, int end)    //Generate passwords and call writer to file
{
    for (int i = start; i < end && !m_passwordNotFound.test(); i++)
    {
        std::string password = GeneratePassword(i);

        if (password == GetPassword())
        {
            m_passwordNotFound.test_and_set();
            fileHandling::FileHandler fileWrite;
            fileWrite.WriteToFile(password);
        }
    }
}

int bruteforce::Bruteforce::AmountPassword()   // Calculate all possible password
{
    int amountPassword = 0;
    for (int i = m_length; i > 0; --i)
    {
        amountPassword += std::pow(m_availableSymbol.size(), i);
    }
    return amountPassword;
}

std::string bruteforce::Bruteforce::GeneratePassword(uint64_t index)   //Generete Password from  the transmitted sequence numbers
{
    int length{};
    uint64_t counter{};
    if (index)
    {
        do
        {
            ++length;
            counter += std::pow(m_availableSymbol.size(), length);
            if (length == 1)
            {
                --counter;
            }
        } while (counter < index);
    }
    else
    {
        length = 1;
    }
    std::string password{};
    counter = index;
    for (int i = 1; i < length; ++i)
    {
        counter -= std::powl(m_availableSymbol.size(), i);
    }
    for (int i = 0; i < length; ++i)
    {
        uint64_t ch = counter % m_availableSymbol.size();
        password = m_availableSymbol[ch] + password;
        counter /= m_availableSymbol.size();
    }
    return password;
}