//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"

using namespace ClassProject;

TEST (Getstat, testvariables) {
    std::unique_ptr<ClassProject::Reachability> fsm = std::make_unique<ClassProject::Reachability>(3);
    std::vector<BDD_ID> stateVars2 = fsm->getStates();
    EXPECT_EQ (stateVars2.size(), 3);                   //check that the nr of vars is as stated when init
    EXPECT_EQ (stateVars2[0], 2);                       // check each var if they have the right ID
    EXPECT_EQ (stateVars2[1], 3);
    EXPECT_EQ (stateVars2[2], 4);
}

TEST (function, iscorrect) {
    std::unique_ptr<ClassProject::Reachability> fsm = std::make_unique<ClassProject::Reachability>(2);
    std::vector<BDD_ID> stateVars = fsm->getStates();
    BDD_ID first = fsm->or2(stateVars[0], 1);
    BDD_ID second = fsm->or2(stateVars[1], 1);           //check that the first time Identity function is present
    EXPECT_THROW(fsm->setTransitionFunctions({first,second,0}),std::runtime_error);
    EXPECT_TRUE(fsm->isReachable({false, false}));  //check transition function initialised correctly
    EXPECT_FALSE(fsm->isReachable({false, true}));
    EXPECT_FALSE(fsm->isReachable({true, false}));
    EXPECT_FALSE(fsm->isReachable({true, true}));
    fsm->setTransitionFunctions({first, second});         //set transition function
    EXPECT_TRUE(fsm->isReachable({false, false}));  //check transition function when set gives correct state set
    EXPECT_FALSE(fsm->isReachable({false, true}));
    EXPECT_FALSE(fsm->isReachable({true, false}));
    EXPECT_TRUE(fsm->isReachable({true, true}));
}

TEST (initstates, iscorrect) {
    std::unique_ptr<ClassProject::Reachability> fsm = std::make_unique<ClassProject::Reachability>(2);
    EXPECT_THROW(fsm->setInitState({true, true, true,true}),std::runtime_error);
    EXPECT_TRUE(fsm->isReachable({false, false}));  //check init state initialised correctly
    EXPECT_FALSE(fsm->isReachable({false, true}));
    EXPECT_FALSE(fsm->isReachable({true, false}));
    EXPECT_FALSE(fsm->isReachable({true, true}));
    fsm->setInitState({true, true});
    EXPECT_FALSE(fsm->isReachable({false, false})); //check init state set correctly
    EXPECT_FALSE(fsm->isReachable({false, true}));
    EXPECT_FALSE(fsm->isReachable({true, false}));
    EXPECT_TRUE(fsm->isReachable({true, true}));

}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
