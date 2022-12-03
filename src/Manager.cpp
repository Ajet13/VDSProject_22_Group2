#include "Manager.h"

using namespace ClassProject;

BDD_ID Manager::createVar(const std::string &label){
    unique_table.push_back({unique_table.size(),0,1,unique_table.size(),label});
    return unique_table.size();
}
//const BDD_ID &True(){}
//const BDD_ID &False(){}
//bool isConstant(BDD_ID f){}
//bool isVariable(BDD_ID x){}
//BDD_ID topVar(BDD_ID f){}
//BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e){}
//BDD_ID coFactorTrue(BDD_ID f, BDD_ID x){}
//BDD_ID coFactorFalse(BDD_ID f, BDD_ID x){}
//BDD_ID coFactorTrue(BDD_ID f){}
//BDD_ID coFactorFalse(BDD_ID f){}
//BDD_ID neg(BDD_ID a){}
//BDD_ID and2(BDD_ID a, BDD_ID b){}
//BDD_ID or2(BDD_ID a, BDD_ID b){}
//BDD_ID xor2(BDD_ID a, BDD_ID b){}
//BDD_ID nand2(BDD_ID a, BDD_ID b){}
//BDD_ID nor2(BDD_ID a, BDD_ID b){}
//BDD_ID xnor2(BDD_ID a, BDD_ID b){}
//std::string getTopVarName(const BDD_ID &root){}
//void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){}
//void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){}
//size_t uniqueTableSize(){}