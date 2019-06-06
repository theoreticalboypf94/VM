//
// Created by alpharius on 06.06.19.
//


#include "Logic_elements.h"
#define BYTE 8

void MUL_8bit::compute_state() {
    MUL elements[8];
    for (int i=0; i<BYTE; i++){
        elements[i].input[0] = input[0][i]; // set A
        elements[i].input[1] = input[1][i]; // set B
        elements[i].input[2] = input[2][0]; // establish SET
    }

    for (int i=0; i<BYTE; i++){
        elements[i].compute_state();
    }

    for (int i=0; i<BYTE; i++){
        state[i] = elements[i].state;
    }
}

void MUL_8bit::read_A_B_SET(char *A, char *B, char *SET) {
    for (int i=00; i<BYTE; i++){
        input[0][i] = *(A+i) - 48;
        input[1][i] = *(B+i) -48;  // magic number '0' is 48!
    }
    input[2][0] = *SET;
}

