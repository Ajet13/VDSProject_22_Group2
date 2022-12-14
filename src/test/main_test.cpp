//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include "Manager.h"

using namespace ClassProject;
Manager *man = new Manager();
BDD_ID a_var = man->createVar("a"); //create new var
BDD_ID b_var = man->createVar("b");

TEST (CreatevarTest, createvar) {
    EXPECT_EQ (man->createVar("a"), a_var); //check if it finds repeat variable
    EXPECT_EQ (man->createVar("c"), b_var + 1); //check new variable
}

TEST (trueTest, istrue) {
    EXPECT_EQ (man->True(), 1);
}

TEST (falseTest, isfalse) {
    EXPECT_EQ (man->False(), 0);
}

TEST (tableTest, tablesize) {
    EXPECT_EQ (man->uniqueTableSize(), man->unique_table.size());
    EXPECT_EQ (man->uniqueTableSize(), 5);
}

TEST (topvarTest, findname) {
    EXPECT_EQ (man->getTopVarName(a_var), "a");
}

TEST (topvarTest, findvalue) {
    EXPECT_EQ (man->topVar(a_var), 2);
}

TEST (constantest, constant) {
    EXPECT_FALSE(man->isConstant(a_var));
    EXPECT_TRUE(man->isConstant(man->True()));
}

TEST (variabletest, variable) {
    EXPECT_TRUE(man->isVariable(a_var));
    EXPECT_FALSE(man->isVariable(man->False()));
}

TEST (COFTtest, Tnode) {
    EXPECT_EQ(man->coFactorTrue(a_var), man->True());
}

TEST (COFFtest, Fnode) {
    EXPECT_EQ(man->coFactorFalse(a_var), man->False());
}

TEST (COFT2test, respectto) {
    EXPECT_EQ(man->coFactorTrue(a_var, a_var), man->True());
    EXPECT_EQ(man->coFactorTrue(a_var, b_var), a_var);
    EXPECT_EQ(man->coFactorTrue(b_var, a_var), b_var);
}

TEST (COFF2test, respectto) {
    EXPECT_EQ(man->coFactorFalse(a_var, a_var), man->False());
    EXPECT_EQ(man->coFactorFalse(a_var, b_var), a_var);
    EXPECT_EQ(man->coFactorFalse(b_var, a_var), b_var);
}

TEST (itetest, variale) {
    EXPECT_EQ(man->ite(a_var, a_var, man->False()), a_var);
}

TEST (andtest, variables) {
    EXPECT_EQ(man->and2(man->False(), man->False()), man->False()); // 0 and 0 give 0
    EXPECT_EQ(man->and2(man->True(), man->False()), man->False());
    EXPECT_EQ(man->and2(man->False(), man->True()), man->False());
    EXPECT_EQ(man->and2(man->True(), man->True()), man->True()); // 1 and 1 give 1
    EXPECT_EQ(man->and2(a_var, b_var), 5); // a and b gives new bdd labeled 5
}

TEST (ortest, variables) {
    EXPECT_EQ(man->or2(man->False(), man->False()), man->False()); // 0 and 0 give 0
    EXPECT_EQ(man->or2(man->False(), man->True()), man->True());
    EXPECT_EQ(man->or2(man->True(), man->False()), man->True()); // 1 and 0 give 1
    EXPECT_EQ(man->or2(man->True(), man->True()), man->True());
    EXPECT_EQ(man->or2(a_var, b_var), 6); // a or b gives new bdd labeled 6
}

TEST (negtest, variables) {
    EXPECT_EQ(man->neg(man->True()), man->False());
    EXPECT_EQ(man->neg(man->False()), man->True());
    EXPECT_EQ(man->neg(b_var), 7); // new Bdd as 7
}

TEST (xortest, variables) {
    EXPECT_EQ(man->xor2(man->False(), man->False()), man->False()); // 0 and 0 give 0
    EXPECT_EQ(man->xor2(man->False(), man->True()), man->True());
    EXPECT_EQ(man->xor2(man->True(), man->False()), man->True()); // 1 and 0 give 1
    EXPECT_EQ(man->xor2(man->True(), man->True()), man->False());
    EXPECT_EQ(man->xor2(a_var, b_var), 8); // a xor b gives new bdd labeled 8
}

TEST (nandtest, variables) {
    EXPECT_EQ(man->nand2(man->False(), man->False()), man->True()); // 0 and 0 give 1
    EXPECT_EQ(man->nand2(man->False(), man->True()), man->True());
    EXPECT_EQ(man->nand2(man->True(), man->False()), man->True()); // 1 and 0 give 1
    EXPECT_EQ(man->nand2(man->True(), man->True()), man->False());
    EXPECT_EQ(man->nand2(a_var, b_var), 9); // a nand b gives new bdd labeled 9
}

TEST (nortest, variables) {
    EXPECT_EQ(man->nor2(man->False(), man->False()), man->True()); // 0 and 0 give 0
    EXPECT_EQ(man->nor2(man->False(), man->True()), man->False());
    EXPECT_EQ(man->nor2(man->True(), man->False()), man->False()); // 1 and 0 give 0
    EXPECT_EQ(man->nor2(man->True(), man->True()), man->False());
    EXPECT_EQ(man->nor2(a_var, b_var), 10); // a nor b gives new bdd labeled 10
}

TEST (xnortest, variables) {
    EXPECT_EQ(man->xnor2(man->False(), man->False()), man->True()); // 0 and 0 give 0
    EXPECT_EQ(man->xnor2(man->False(), man->True()), man->False());
    EXPECT_EQ(man->xnor2(man->True(), man->False()), man->False()); // 1 and 0 give 1
    EXPECT_EQ(man->xnor2(man->True(), man->True()), man->True());
    EXPECT_EQ(man->xnor2(a_var, b_var), 11); // a xnor b gives new bdd labeled 11
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    Manager *t = new Manager();
    BDD_ID a = t->createVar("a");
    BDD_ID b = t->createVar("b");
    BDD_ID c = t->createVar("c");
    BDD_ID d = t->createVar("d");
    BDD_ID fin = t->and2(t->or2(a, b), t->and2(c, d));
    int count = 0;
    for (auto iter: t->unique_table) {
        std::cout << count << "|" << iter.top_var << "|" << iter.node_low << "|" << iter.node_high << "|" << iter.label
                  << "\n";
        count++;
    }
    std::set<BDD_ID> nodeset;
    std::set<BDD_ID> varset;
    t->findNodes(fin, nodeset);
    for (auto it: nodeset) std::cout << it << ",";
    std::cout << "\n";
    t->findVars(fin, varset);
    for (auto it: varset) std::cout << it << ",";
    std::cout << "\n";
    for (auto it: varset) std::cout << t->getTopVarName(it) << ",";
    return ret;
}