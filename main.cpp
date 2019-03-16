#include <iostream>
#include "Logic_elements.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    AND a(1);
    a.input1 = 0;
    a.input2 = 0;
    a.compute_state();
    std::cout <<(int) a.state;
    return 0;
}