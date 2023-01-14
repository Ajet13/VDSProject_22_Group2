#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"
#include "vector"
#include "iostream"

namespace ClassProject {

    class Reachability : public ReachabilityInterface {
    public:
        std::vector<BDD_ID> current_states;       //state variables
        std::vector<BDD_ID> next_states;
        std::vector<BDD_ID> transition_functions;     //transition function
        std::vector<bool> init_states;       //initial states
    public:
        explicit Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {
            if (stateSize == 0)
                throw std::runtime_error("Invalid state size, should not be 0");  //@interface doc, requirement for ctor
            else {
                for (unsigned int i = 0; i < stateSize; i++) {
                    init_states.push_back(false);
                    current_states.push_back(Manager::createVar("s"+ std::to_string(i))); //use of labels as createvar method doesn't accept same label var
                }
                for (unsigned int i = 0; i < stateSize; i++){
                    next_states.push_back(Manager::createVar("s'"+std::to_string(i)));
                }
                transition_functions = current_states; //transition function is identity function A*1 or A+0 gives A so same ID
            }
        }

        const std::vector<BDD_ID> &getStates() const override;

        //bool isReachable(const std::vector<bool> &stateVector) override;

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) override;

        void setInitState(const std::vector<bool> &stateVector) override;
    };

}
#endif
