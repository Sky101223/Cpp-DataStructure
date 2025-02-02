#include <iostream>
#include "Array.hpp"

int main(void)
{
    Owe::Array<char, 13> hello{ 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '?', '\0' };

    for (char& i : hello)
    {
        std::cout << i;
    }
    std::cout << std::endl;

    hello.at(11) = '!';

    for (Owe::Array<char, 13>::iterator i = hello.begin();
        i != hello.end(); ++i)
    {
        std::cout << *i << std::endl;
    }

    return 0;
}