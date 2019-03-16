//
// Created by alpharius on 16.03.19.
//

#include "Logic_elements.h"

void Logic_elements::pass_state(char order) {
    if (order == 1)
        for(int i=0; i<out.size(); i++)
            out[i]->input1 = state;
    else
        for(int i=0; i<out.size(); i++)
            out[i]->input2 = state;
}

Logic_elements::Logic_elements(char _state) {
    state = _state;
}