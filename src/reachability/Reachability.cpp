#include "Reachability.h"
#include "vector"

using namespace ClassProject;

const std::vector<BDD_ID> &Reachability::getStates() const {
    return current_states; //this contains state variables
}

bool Reachability::isReachable(const std::vector<bool> &stateVector) {
    if (stateVector.size() != current_states.size())
        throw std::runtime_error("no match to the number of state bits with states asked");
    BDD_ID tao = Manager::True();
    for (unsigned int i = 0; i < next_states.size(); i++)
        tao = and2(xnor2(next_states[i], transition_functions[i]), tao);
    BDD_ID Cs = Manager::True();
    for (unsigned int i = 0; i < current_states.size(); i++)
        Cs = and2(xnor2(current_states[i], init_states[i]), Cs);
    BDD_ID Crit, img_curr, img_next, Cr;
    Crit = Cs;
    do {
        Cr = Crit;
        img_next = and2(Cr, tao);
        //https://stackoverflow.com/questions/3623263/reverse-iteration-with-an-unsigned-loop-variable
        for (unsigned int i = current_states.size(); i-- > 0;)
            img_next = or2(coFactorTrue(img_next, current_states[i]), coFactorFalse(img_next, current_states[i]));
        img_curr = img_next;
        for (unsigned int i = 0; i < current_states.size(); i++)
            img_curr = and2(img_curr, xnor2(current_states[i], next_states[i]));
        for (unsigned int i = current_states.size(); i-- > 0;)
            img_curr = or2(coFactorTrue(img_curr, next_states[i]), coFactorFalse(img_curr, next_states[i]));
        Crit = or2(Cr, img_curr);
    } while (Crit != Cr);
    BDD_ID eval = Cr;
    for (unsigned int i = 0; i < stateVector.size(); i++) {
        if (stateVector[i])
            eval = coFactorTrue(eval, current_states[i]);
        else
            eval = coFactorFalse(eval, current_states[i]);
    }
    return eval;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) {
    if (transitionFunctions.size() != next_states.size())
        throw std::runtime_error("no match of transition functions with state bits");
    auto maximum = std::max_element(transitionFunctions.begin(), transitionFunctions.end());
    if (*maximum > Manager::uniqueTableSize() - 1)
        throw std::runtime_error("An unknown ID is provided from transition function");
    transition_functions = transitionFunctions;
}

void Reachability::setInitState(const std::vector<bool> &stateVector) {
    if (stateVector.size() != init_states.size())
        throw std::runtime_error("no match of state size with number state bits");
    init_states = stateVector;
}