//
// Created by alpharius on 16.03.19.
//

#ifndef VM_LOGIC_ELEMENTS_H
#define VM_LOGIC_ELEMENTS_H
#include <vector>

class Logic_elements {
private:

    void pass_state(char order);
    virtual void compute_state() = 0;
public:
    char input1, input2;
    std::vector<Logic_elements*> out;
    char state = 0;
    //Logic_elements(Logic_elements* first, Logic_elements* second);
    Logic_elements(char state);
};


class XOR:public Logic_elements{
public:
    void compute_state(){
        state = input1 ^ input2;
    }
    XOR(char state): Logic_elements(state) {};
};


class AND:public Logic_elements{
public:
    void compute_state(){
        state = input1 && input2;
    }
    AND(char state): Logic_elements(state) {};
};

class OR:public Logic_elements{
public:
    void compute_state(){
        state = input1 || input2;
    }
    OR(char state): Logic_elements(state) {};
};

class AND_NOT:public Logic_elements{
public:
    void compute_state(){
        state = ! (input1 && input2);
    }
    AND_NOT(char state): Logic_elements(state) {};
};


#endif //VM_LOGIC_ELEMENTS_H
