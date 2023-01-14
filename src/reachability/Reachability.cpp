#include "Reachability.h"
#include "vector"

using namespace ClassProject;
const std::vector<BDD_ID> &Reachability::getStates() const{
    return current_states; //this contains state variables
}

//bool isReachable(const std::vector<bool> &stateVector) {}

//void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) {}

//void setInitState(const std::vector<bool> &stateVector) {}