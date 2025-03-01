/// 手撕STL测试
/// 是否能正常运行，是否能过编译

#include <iostream>
#include <algorithm>

#include "Memory.hpp"
#include "ReverseIterator.hpp"
#include "Array.hpp"
#include "AVL.hpp"


int main(void)
{
    Owe::Array<char, 13> hello{ 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '?', '\0' };
    Owe::Tree::AVLTree<char> helloTree;

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
        helloTree.insert(*i);
    }

    for (Owe::Array<char, 13>::reverse_iterator i = hello.rbegin();
        i != hello.rend(); ++i)
    {
        std::cout << *i;
    }
    std::cout << std::endl;

    helloTree.printTree();

    if (helloTree.find('l')) {
        std::cout << "Find 'l' path: " << helloTree.findPosition('l') << std::endl;
    }
    else {
        std::cout << "No found 'l'" << std::endl;
    }

    return 0;
}