#ifndef LEH
#define LEH
#include <vector>

class Logic_element{
public:
    virtual void compute_state() = 0;
    std::vector<char> input;
    std::vector<Logic_element*> out;
    void push_state(std::vector<char> order);
    char state = 0;
    Logic_element(char _state);
};

class XOR:public Logic_element{
public:
    void compute_state(){
        state = input[0] ^ input[1];
    }
    XOR(char state): Logic_element(state) {
        input.resize(2);
    };
    XOR(): Logic_element(0) {
        input.resize(2);
    };
};

class AND:public Logic_element{
public:
    void compute_state(){
        state = input[0] && input[1];
    }
    AND(char state): Logic_element(state) {
        input.resize(2);
    };
    AND(): Logic_element(0) {
        input.resize(2);
    };
};

class OR:public Logic_element{
public:
    void compute_state(){
        state = input[0] || input[1];
    }
    OR(char state): Logic_element(state) {
        input.resize(2);
    };
    OR(): Logic_element(0) {
        input.resize(2);
    };
};

class NOT: public Logic_element{
public:
    void compute_state(){
        state = (input[0] == 0)? 1 : 0;
    }
    NOT(): Logic_element(0) {
        input.resize(1);
    }
};

class AND_NOT:public Logic_element{
public:
    void compute_state(){
        state = ! (input[0] && input[1]);
    }
    AND_NOT(char state): Logic_element(state) {
        input.resize(2);
    };
    AND_NOT(): Logic_element(0) {
        input.resize(2);
    };
};

class I: public Logic_element{
public:
    void compute_state(){
        state = input[0];
    }
    I(): Logic_element(0) {input.resize(1);};
};

class MUL: public Logic_element{
    /*
     *  That is multiplexer unit which translate selected input forward
     *  https://www-users.cs.york.ac.uk/~mjf/simple_cpu/Images/mux2.jpg
     *            ___________
     *          A |insert0  |
     *          B |insert1  |  -- or (A if sel == 0) or (B if sel == 1)
     *        SEL |insert2__|
     */
public:
    MUL(): Logic_element(0) {input.resize(3);}
    void compute_state(){
        AND and1, and2;
        OR out;
        NOT inv1;
        and1.out.push_back(&out); //0
        and2.out.push_back(&out); //1
        inv1.out.push_back(&and1); // sel

        and1.input[0] = input[0];  //A
        inv1.input[0] = input[2];  //SEL
        and2.input[0] = input[2];  //SEL
        and2.input[1] = input[1];  //B

        inv1.compute_state();
        inv1.push_state({1});     //подаем инверсию на 2ю клемку
        and1.compute_state();
        and2.compute_state();
        and1.push_state({0});
        and2.push_state({1});

        out.compute_state();

        state = out.state;
    }
};

class MUL8bit: public Logic_element{
    MUL8bit(0) {input.resize(17);}
    void compute_state(){

    }
};

class bus8bit{
public:
    std::vector<I> bus;
    std::vector<char> input;
    bus8bit() {bus.resize(8);};

};


#endif