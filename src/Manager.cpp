#include "Manager.h"
#include "algorithm"
#include "iostream"
using namespace ClassProject;
/*for(auto iter : unique_table){
        std::cout<<"//"<<iter.top_var<<"//"<<iter.node_low<<"//"<<iter.node_high<<"//"<<iter.label<<"\n";
    }*/
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
        unique_table.push_back({r_high, r_low, top_variable});
        count=uniqueTableSize()-1; //to be reviewed
    }
    computed_table.push_back({i,t,e,count});
    return count;
}
BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    if(isConstant(f) || isConstant(x) || unique_table[f].top_var > x) return f;
    if(unique_table[f].top_var == x) return unique_table[f].node_high;
    else if(unique_table[f].top_var < x){
        BDD_ID T = coFactorTrue(unique_table[f].node_high,x);
        BDD_ID F = coFactorTrue(unique_table[f].node_low,x);
        return ite(unique_table[f].top_var,T,F);
    }
}
BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    if(isConstant(f) || unique_table[f].top_var > x) return f;
    if(unique_table[f].top_var == x) return unique_table[f].node_low;
    else if(unique_table[f].top_var < x){
        BDD_ID T = coFactorFalse(unique_table[f].node_high,x);
        BDD_ID F = coFactorFalse(unique_table[f].node_low,x);
        return ite(unique_table[f].top_var,T,F);
    }
}
BDD_ID Manager::coFactorTrue(BDD_ID f){
    return coFactorTrue(f, unique_table[f].top_var);
}
BDD_ID Manager::coFactorFalse(BDD_ID f){
    return coFactorFalse(f,unique_table[f].top_var);
}
BDD_ID Manager::neg(BDD_ID a){
    BDD_ID out = ite(a,0,1);
    if(std::empty(unique_table[out].label))unique_table[out].label = "~" + unique_table[a].label; //questionable
    return out;
}
BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    BDD_ID out = ite(a,b,0);
    if(std::empty(unique_table[out].label))unique_table[out].label = unique_table[a].label+"&"+unique_table[b].label; //questionable
    return out;
}
BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    BDD_ID out = ite(a,1,b);
    if(std::empty(unique_table[out].label))unique_table[out].label = unique_table[a].label+"+"+unique_table[b].label; //questionable
    return out;
}
BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
    BDD_ID out = ite(a,neg(b),b);
    if(std::empty(unique_table[out].label))unique_table[out].label = unique_table[a].label+"⊕"+unique_table[b].label; //questionable
    return out;
}
BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
    BDD_ID out = ite(a,neg(b),1);
    if(std::empty(unique_table[out].label))unique_table[out].label = unique_table[a].label+"‾"+unique_table[b].label; //questionable
    return out;
}
BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
    BDD_ID out = ite(a,0,neg(b));
    if(std::empty(unique_table[out].label))unique_table[out].label = unique_table[a].label+"∓"+unique_table[b].label; //questionable
    return out;
}
BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
    BDD_ID out = ite(a,b,neg(b));
    if(std::empty(unique_table[out].label))unique_table[out].label = unique_table[a].label+"⊙"+unique_table[b].label; //questionable
    return out;
}
std::string Manager::getTopVarName(const BDD_ID &root){
    return unique_table[root].label;
}
void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    // if to implement the funct to return also const nodes put first line under if above it
    if(!isConstant(root)){
        nodes_of_root.insert(root);
        findNodes(coFactorTrue(root),nodes_of_root);
        findNodes(coFactorFalse(root),nodes_of_root);
    }
}
void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    std::set<BDD_ID> NOF;
    findNodes(root,NOF);
    for(auto iter:NOF) vars_of_root.insert(topVar(iter));
}
size_t Manager::uniqueTableSize(){
    return unique_table.size();
}