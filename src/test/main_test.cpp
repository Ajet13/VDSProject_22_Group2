//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include "Manager.h"
using namespace ClassProject;
Manager *man = new Manager();
TEST (CreatevarTest, createvar) {
    EXPECT_EQ (man->createVar("label"), 3);
}
TEST (trueTest, istrue) {
    EXPECT_EQ (man->True(), 1);
}
TEST (falseTest, isfalse) {
    EXPECT_EQ (man->False(), 0);
}
TEST (tableTest, tablesize) {
    EXPECT_EQ (man->uniqueTableSize(), 3);
}
TEST (topvarTest, findname) {
    EXPECT_EQ (man->getTopVarName(2), "label");
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
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
