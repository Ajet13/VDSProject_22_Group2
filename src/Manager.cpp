#include "Manager.h"
#include "algorithm"
#include "iostream"
using namespace ClassProject;

BDD_ID Manager::createVar(const std::string &label){
    unique_table.push_back({1,0,unique_table.size(),label});
    return unique_table.size()-1;
}
const BDD_ID &Manager::True(){
    //static const Node test_true = {1,1,1,1,"T"};
    return unique_table[1].top_var;
}
const BDD_ID &Manager::False(){
    //static const Node test_false = {0,0,0,0,"F"};
    return unique_table[0].top_var;
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
BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    if(i==True()) return t;
    if(i==False()) return e;
    if(t==e) return t;
    if(t==True() & e==False()) return i;
    for(auto iter : computed_table){
        if(iter.i==i & iter.e==e & iter.t==t) return(iter.r);
    }
    BDD_ID top_variable = isConstant(t) ? topVar(i): std::min(topVar(i), topVar(t));
    BDD_ID top_variable2 = isConstant(e) ? topVar(i): std::min(topVar(i),topVar(e));
    top_variable = std::min(top_variable,top_variable2);
    BDD_ID r_high = ite(coFactorTrue(i, top_variable), coFactorTrue(t, top_variable), coFactorTrue(e, top_variable));
    BDD_ID r_low = ite(coFactorFalse(i, top_variable), coFactorFalse(t, top_variable), coFactorFalse(e, top_variable));
    if(r_high==r_low) return r_high;
    BDD_ID count=0;
    bool found = false;
    for(auto iter : unique_table){
        if(iter.top_var==top_variable & iter.node_high==r_high & iter.node_low==r_low){
            //std::cout<<"//"<<iter.top_var<<"//"<<iter.node_low<<"//"<<iter.node_high<<"//"<<iter.label<<"\n";
            found=true;
            break;
        }
        count++;
    }
    if(!found) {
        unique_table.push_back({top_variable, r_low, r_high});
        count=uniqueTableSize()-1; //to be reviewed
    }
    computed_table.push_back({i,t,e,count});
    return count;
}
BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    if(isConstant(f) || unique_table[f].top_var > x) return f;
    if(unique_table[f].top_var == x) return coFactorTrue(f);
}
BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    if(isConstant(f) || unique_table[f].top_var > x) return f;
    if(unique_table[f].top_var == x) return coFactorFalse(f);
}
BDD_ID Manager::coFactorTrue(BDD_ID f){
    return unique_table[f].node_high;
}
BDD_ID Manager::coFactorFalse(BDD_ID f){
    return unique_table[f].node_low;
}
//BDD_ID neg(BDD_ID a){}
BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    BDD_ID out = ite(a,b,0);
    unique_table[out].label = unique_table[a].label+"&"+unique_table[b].label; //questionable
    //for(auto iter : unique_table){
    //        std::cout<<"//"<<iter.top_var<<"//"<<iter.node_low<<"//"<<iter.node_high<<"//"<<iter.label<<"\n";
    //}
    return out;
}
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