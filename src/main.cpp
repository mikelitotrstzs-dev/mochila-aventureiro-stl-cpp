#include "Interface.hpp"
#include <iostream>
int main() {
    Interface interface(std::cin, std::cout);
    interface.executar();
    return 0;
}
