#include <iostream>
#include "Logic_elements.h"
#define MUL_TEST

int main(){

    // ТЕСТИРОВАНИЕ МУЛЬТИПЛЕКСЕРА
#ifdef MUL_TEST
    MUL m;
    std::cout << "SEL\tA\tB\tRESULT\n";
    for(char SEL=0; SEL<2; SEL++){
        for (char A=0; A<2; A++){
            for (char B=0; B<2; B++){
                m.input[0] = A;
                m.input[1] = B;
                m.input[2] = SEL;
                m.compute_state();
                std::cout << (int)SEL << "\t"
                << (int) A << "\t"
                << (int) B << "\t"
                << (int) m.state << "\n";
            }
        }
    }
#endif

    return 0;
}