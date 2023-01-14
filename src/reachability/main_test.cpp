//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"
using namespace ClassProject;


TEST (Getstat,testvariables) {
    std::unique_ptr<ClassProject::Reachability> fsm2 = std::make_unique<ClassProject::Reachability>(3);
    std::vector<BDD_ID> stateVars2 = fsm2->getStates();
    EXPECT_EQ (stateVars2.size(), 3);                   //check that the nr of vars is as stated when init
    EXPECT_EQ (stateVars2[0], 2);                       // check each var if they have the right ID
    EXPECT_EQ (stateVars2[1], 3);
    EXPECT_EQ (stateVars2[2], 4);
}
TEST (function, iscorrect) {
    std::unique_ptr<ClassProject::Reachability> fsm2 = std::make_unique<ClassProject::Reachability>(3);
    std::vector<BDD_ID> stateVars = fsm2->getStates();
    BDD_ID first=fsm2->and2(stateVars[0], stateVars[1]);
    BDD_ID second=fsm2->and2(stateVars[1], stateVars[2]);
    BDD_ID third=fsm2->and2(stateVars[2], stateVars[0]);
    EXPECT_EQ (fsm2->transition_functions.size(),3);            //check that the first time Identity function is present
    EXPECT_EQ (fsm2->transition_functions[0],stateVars[0]);
    EXPECT_EQ (fsm2->transition_functions[1],stateVars[1]);
    EXPECT_EQ (fsm2->transition_functions[2],stateVars[2]);
    fsm2->setTransitionFunctions({first,second,third});         //set transition function
    EXPECT_EQ (fsm2->transition_functions.size(),3);            //check if set correctly
    EXPECT_EQ (fsm2->transition_functions[0],first);
    EXPECT_EQ (fsm2->transition_functions[1],second);
    EXPECT_EQ (fsm2->transition_functions[2],third);
}
TEST (initstates, iscorrect) {
    std::unique_ptr<ClassProject::Reachability> fsm2 = std::make_unique<ClassProject::Reachability>(3);
    EXPECT_EQ (fsm2->init_states.size(),3);            //check that the first states are false
    EXPECT_FALSE(fsm2->init_states[0]);
    EXPECT_FALSE(fsm2->init_states[1]);
    EXPECT_FALSE(fsm2->init_states[2]);
    fsm2->setInitState({true,true,true});
    EXPECT_EQ (fsm2->init_states.size(),3);            //check that after change correct value is set
    EXPECT_TRUE(fsm2->init_states[0]);
    EXPECT_TRUE(fsm2->init_states[1]);
    EXPECT_TRUE(fsm2->init_states[2]);

}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
