#include <stdio.h>
#include <stdbool.h>
// in future it will be separete header commands.h
// https://blog.felixangell.com/virtual-machine-in-c/
typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
    A, B, C, D, E, F,
    NUM_OF_REGISTERS
} Registers;


const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

// fetching the current instruction

int ip = 0;
int sp = -1;
int stack[256];

int fetch() {
    return program[ip];
}

bool running = true;

void eval(int instr){
    switch (instr) {
        case HLT:
            running = false;
            break;
        case PSH:
            sp++;
            stack[sp] = program[++ip];
            break;
        case POP:{
                     int val_popped = stack[sp--];
                     printf("popped %d\n", val_popped);
                     break;
                 }
        case ADD:{
                    int a = stack[sp--];
                    int b = stack[sp--];
                    int result = a + b;
                    sp++;
                    stack[sp] = result;
                    break;
                 }
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }

    return 0;
}
