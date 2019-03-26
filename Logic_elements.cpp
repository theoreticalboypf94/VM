#include "Logic_elements.h"

void Logic_element::push_state(std::vector<char> order) {
    for(size_t i=0; i<order.size(); i++){
        out[i]->input[order[i]] = state;
    }
}

Logic_element::Logic_element(char _state) {
    state = _state;
}