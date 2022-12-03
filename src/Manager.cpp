#include "Manager.h"

using namespace ClassProject;

BDD_ID Manager::createVar(const std::string &label){
    unique_table.push_back({unique_table.size(),1,0,unique_table.size(),label});
    return unique_table.size();
}
const BDD_ID &Manager::True(){
    static const Node test_true = {1,1,1,1,"T"};
    return test_true.node;
}
const BDD_ID &Manager::False(){
    static const Node test_false = {0,0,0,0,"F"};
    return test_false.node;
}
bool Manager::isConstant(BDD_ID f){
    return unique_table[f].node_high==unique_table[f].node_low;
}
bool Manager::isVariable(BDD_ID x){
    return unique_table[x].node_high==True() && unique_table[x].node_low==False();
}
BDD_ID Manager::topVar(BDD_ID f){
    return unique_table[f].top_var;
}
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
std::string Manager::getTopVarName(const BDD_ID &root){
    return unique_table[root].label;
}
//void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){}
//void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){}
size_t Manager::uniqueTableSize(){
    return unique_table.size();
}