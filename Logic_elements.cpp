#include "Logic_elements.h"

void Logic_element::push_state(std::vector<char> order) {
    // с одного входна на много выходов, полезно при реализации композиции И ИЛИ НЕ, на более широких выходах
    // не применим, требует переопределения для мультиплексера (или нет)
    for(size_t i=0; i<order.size(); i++){
        out[i]->input[order[i]] = state;
    }
}

Logic_element::Logic_element(char _state) {
    state = _state;
}