#include <iostream>
#include "Logic_elements.h"
#include "stdio.h"

//                      TEST CASES
#define MUL_TEST
#define MUL_8BIT_TEST

//                      CONSTANTS
#define BYTE 8

int main(){

    // ТЕСТИРОВАНИЕ МУЛЬТИПЛЕКСЕРА
#ifdef MUL_TEST
    printf("\ttest of table of true for MUL\n");
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
    printf("\n\n");
#endif

#ifdef MUL_8BIT_TEST
    // всеравно русские будут читать, добавил тест на 8-битный мультиплексер. норм работает
    // важно "0" это 48 в интеджере
    printf("\ttest of 8bim multiplexer\n");

    MUL_8bit m8b;
    m8b.read_A_B_SET("11110000", "00001111","0");
    m8b.compute_state();
    for (int i=0; i<BYTE; i++)
        printf("%d", m8b.state[i]);


#endif //MUL_8BIT_TEST


    return 0;
}