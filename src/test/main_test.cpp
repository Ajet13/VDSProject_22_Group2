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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
