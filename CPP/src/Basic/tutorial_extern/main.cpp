#include <iostream>
#include "global.hpp"

int main() {
    std::cout << "Hello, World!\n";
    std::cout << "Global age is " << globalAge << '\n';
    std::cout << "Global name is " << globalName << std::endl;
    
    return 0;
}