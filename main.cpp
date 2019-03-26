#include <iostream>
#include "Logic_elements.h"

int main(){
//    XOR a,b;
//    I c,d;
//    std::string i1, i2;
//
//    a.out.push_back(&b);
//    a.out.push_back(&c);
//
//    b.out.push_back(&a);
//    b.out.push_back(&d);
//
//    for(;;){
//        //std::cin >>  a.input[0] >>  b.input[1];
//        std::cin >> i1 >> i2;
//        a.input[0] = std::stoi(i1);
//        b.input[1] = std::stoi(i2);
//        a.compute_state();
//        b.compute_state();
//        a.push_state({0,0});
//        b.push_state({1,0});
//        c.compute_state();
//        d.compute_state();
//
//        std::cout << "RESULT " << (int) c.state << " "
//        <<(int) d.state << std::endl;
//    }

    //MUL
    //NOT n;
    //n.input[0] = 0;
    //n.compute_state();
    //std::cout << (int) n.state;
    MUL m;
    std::string A, B, SEL;
    for(;;){
        std::cin >> A >> B >> SEL;
        m.input[0] = std::stoi(A);
        m.input[1] = std::stoi(B);
        m.input[2] = std::stoi(SEL);

        m.compute_state();
        std::cout << (int) m.state << std::endl;
    }

    return 0;
}