#include "Reachability.h"
#include "vector"

using namespace ClassProject;
const std::vector<BDD_ID> &Reachability::getStates() const{
    return current_states; //this contains state variables
}

//bool isReachable(const std::vector<bool> &stateVector) {}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) {
    if(transitionFunctions.size()!=next_states.size())
        throw std::runtime_error("no match of transition functions with state bits");
    auto maximum = std::max_element(transitionFunctions.begin(), transitionFunctions.end());
    if(*maximum > Manager::uniqueTableSize()-1)
        throw  std::runtime_error("An unknown ID is provided from transition function");
    transition_functions=transitionFunctions;
}

void Reachability::setInitState(const std::vector<bool> &stateVector) {
    if(stateVector.size()!=init_states.size())
        throw std::runtime_error("no match of state size with number state bits");
    init_states=stateVector;
}