//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include "Manager.h"
using namespace ClassProject;
Manager *man = new Manager();
TEST (CreatevarTest, createvar) {
    //BDD_ID a_var = man->createVar("a");
    EXPECT_EQ (man->createVar("a"), 2);
    EXPECT_EQ (man->createVar("b"), 3);
}
TEST (trueTest, istrue) {
    EXPECT_EQ (man->True(), 1);
}
TEST (falseTest, isfalse) {
    EXPECT_EQ (man->False(), 0);
}
TEST (tableTest, tablesize) {
    EXPECT_EQ (man->uniqueTableSize(), 4);
}
TEST (topvarTest, findname) {
    EXPECT_EQ (man->getTopVarName(2), "a");
}
TEST (topvarTest, findvalue) {
    EXPECT_EQ (man->topVar(2), 2);
}
TEST (constantest, constant) {
    EXPECT_FALSE(man->isConstant(2));
}
TEST (variabletest, variable) {
    EXPECT_TRUE(man->isVariable(2));
}
TEST (COFTtest, Tnode) {
    EXPECT_EQ(man->coFactorTrue(2),1);
}
TEST (COFFtest, Fnode) {
    EXPECT_EQ(man->coFactorFalse(2),0);
}
TEST (COFT2test, respectto) {
    EXPECT_EQ(man->coFactorTrue(2,2),1);
}
TEST (COFF2test, respectto) {
    EXPECT_EQ(man->coFactorFalse(2,2),0);
}
TEST (itetest, variale) {
    EXPECT_EQ(man->ite(2,2,0),2);
}
TEST (andtest, variables) {
    EXPECT_EQ(man->and2(1,0),0); // 1 and 0 give 0
    EXPECT_EQ(man->and2(1,1),1); // 1 and 1 give 1
    EXPECT_EQ(man->and2(3,2),4); // a and b gives new bdd labeled 4
}
TEST (ortest, variables) {
    EXPECT_EQ(man->or2(0,0),0); // 1 and 0 give 0
    EXPECT_EQ(man->or2(1,0),1); // 1 and 1 give 1
    EXPECT_EQ(man->or2(2,3),5); // a or b gives new bdd labeled 5
}
TEST (xortest, variables) {
    EXPECT_EQ(man->xor2(0,0),0); // 1 and 0 give 0
    EXPECT_EQ(man->xor2(1,0),1); // 1 and 1 give 1
    EXPECT_EQ(man->xor2(2,3),7); // a xor b gives new bdd labeled 5
}
TEST (negtest, variables) {
    EXPECT_EQ(man->neg(0),1); // 1 and 0 give 0
    EXPECT_EQ(man->neg(1),0); // 1 and 1 give 1
    EXPECT_EQ(man->neg(3),6); // a xor b gives new bdd labeled 5
}
TEST (nandtest, variables) {
    EXPECT_EQ(man->nand2(0,0),1); // 1 and 0 give 0
    EXPECT_EQ(man->nand2(1,1),0); // 1 and 1 give 1
    EXPECT_EQ(man->nand2(2,3),8); // a xor b gives new bdd labeled 5
}
TEST (nortest, variables) {
    EXPECT_EQ(man->nor2(0,0),1); // 1 and 0 give 0
    EXPECT_EQ(man->nor2(1,0),0); // 1 and 1 give 1
    EXPECT_EQ(man->nor2(2,3),9); // a xor b gives new bdd labeled 5
}
TEST (xnortest, variables) {
    EXPECT_EQ(man->xnor2(0,0),1); // 1 and 0 give 0
    EXPECT_EQ(man->xnor2(1,0),0); // 1 and 1 give 1
    EXPECT_EQ(man->xnor2(2,3),10); // a xor b gives new bdd labeled 5
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    int count = 0;
    for(auto iter : man->unique_table){
        std::cout<<count<<"|"<<iter.top_var<<"|"<<iter.node_low<<"|"<<iter.node_high<<"|"<<iter.label<<"\n";
        count++;
    }
    return 1;
}
