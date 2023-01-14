#include "Reachability.h"
#include "vector"

using namespace ClassProject;

const std::vector<BDD_ID> &Reachability::getStates() const {
    return current_states; //this contains state variables
}

bool Reachability::isReachable(const std::vector<bool> &stateVector) {
    //compute transition relation
    //based on assignment example func is τ = (s′0 δ0 + s¯′0 δ¯0 ) ∗ (s′1 δ1 + s¯′1 δ¯1 )
    // logically as andn(xnor2(s′n, δn),xnor2(s′n+1, δn+1))...
    BDD_ID tao = Manager::True();
    for (unsigned int i = 0; i < next_states.size(); i++)
        tao = and2(xnor2(next_states[i], transition_functions[i]), tao);
    //compute characteristic function of initial states
    //similar to above we compute characteristic function of initial states
    //cs = (s0 == 0) ∗ (s1 == 0) = (s0 ⊕ 0) ∗ (s1 ⊕ 0) <= with overline
    //logically  as andn(xnor2(sn,init_n),xnor2(sn+1,init_+1))...
    BDD_ID Cs = Manager::True();
    for (unsigned int i = 0; i < current_states.size(); i++)
        Cs = and2(xnor2(current_states[i], init_states[i]), Cs);
    BDD_ID Crit, img_curr, img_next, Cr;
    //crit=cs
    Crit = Cs;
    do {
        //cr=crit
        Cr = Crit;
        //compute image of next states
        //from example temp1 = cR ∗ τ
        //temp2 = coF actorT rue(temp1, s1 ) + coF actorF alse(temp1, s1 )
        //img(s′0 , s′1 ) = coF actorT rue(temp2, s0 ) + coF actorF alse(temp2, s0 )
        //can be deduced the algorithm below
        img_next = and2(Cr, tao);
        for (unsigned int i = current_states.size() - 1; i != 0; i--)
            img_next = or2(coFactorTrue(img_next, current_states[i]), coFactorFalse(img_next, current_states[i]));
        //compute image of current states
        //from example temp1 = (s0 ⊕ s′0 ) ∗ (s1 ⊕ s′1 ) ∗ img(s′0 , s′1 )
        //temp2 = coF actorT rue(temp1, s′1 ) + coFactorFalse(temp1, s′1 )
        //img(s0 , s1 ) = coF actorT rue(temp2, s′0 ) + coFactorFalse(temp2, s′0 )
        img_curr = img_next;
        for (unsigned int i = 0; i < current_states.size(); i++)
            img_curr = and2(img_curr, xnor2(current_states[i], next_states[i]));
        for (unsigned int i = current_states.size() - 1; i != 0; i--)
            img_curr = or2(coFactorTrue(img_curr, next_states[i]), coFactorFalse(img_curr, next_states[i]));
        //compute new crit
        Crit = or2(Cr, img_curr);
        //check if crit==cr
    } while (Crit != Cr);
    //evaluate if the state is present
    BDD_ID eval = Cr;
    for (unsigned int i = 0; i < stateVector.size(); i++) {
        std::cout<<stateVector[i]<<std::endl;
        if (stateVector[i])
            eval = coFactorTrue(eval, current_states[i]);
        else
            eval = coFactorFalse(eval, current_states[i]);
    }
    //return evaluation
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