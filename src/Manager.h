// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H
//#include "stdlib.h"
#include "vector"
#include "algorithm"
#include "ManagerInterface.h"
#include "unordered_map"
#include "boost/functional/hash.hpp"

namespace ClassProject {
//using namespace ClassProject;
    class Manager : public ManagerInterface {
    public:
        struct Node {
            BDD_ID node_high;
            BDD_ID node_low;
            BDD_ID top_var;
            std::string label;
        };
        struct new_Node {
            BDD_ID node_high;
            BDD_ID node_low;
            BDD_ID top_var;
            bool operator==(const new_Node &other) const
            { return (node_low == other.node_low
                      && node_high == other.node_high
                      && top_var == other.top_var);
            }
        };
        struct NodeHasher
        {
            std::size_t operator()(const new_Node& nN) const
            {
                std::size_t seed=0;
                using boost::hash_value;
                using boost::hash_combine;
                //ref: https://valelab4.ucsf.edu/svn/3rdpartypublic/boost-versions/boost_1_55_0/doc/html/hash/combine.html
                hash_combine(seed,hash_value(nN.node_high));
                hash_combine(seed,hash_value(nN.node_low));
                hash_combine(seed,hash_value(nN.top_var));
                return seed;
            }
        };
        /*struct CTNode {
            BDD_ID i;
            BDD_ID t;
            BDD_ID e;
            BDD_ID r;
        };*/
        struct CTNode_new{
            BDD_ID i;
            BDD_ID t;
            BDD_ID e;
            bool operator==(const CTNode_new &other) const
            { return (i == other.i
                      && t == other.t
                      && e == other.e);
            }
        };
        //ref:https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
        struct KeyHasher
        {
            std::size_t operator()(const CTNode_new& CTN) const
            {
                std::size_t seed=0;
                using boost::hash_value;
                using boost::hash_combine;
                //ref: https://valelab4.ucsf.edu/svn/3rdpartypublic/boost-versions/boost_1_55_0/doc/html/hash/combine.html
                hash_combine(seed,hash_value(CTN.i));
                hash_combine(seed,hash_value(CTN.t));
                hash_combine(seed,hash_value(CTN.e));
                return seed;
            }
        };
        std::vector<Node> unique_table; //start unique table
        std::unordered_map<new_Node,BDD_ID,NodeHasher>new_unique_table;
        std::unordered_map<CTNode_new,BDD_ID,KeyHasher>new_ct_table;
        //std::vector<CTNode> computed_table; //start unique table
        BDD_ID createVar(const std::string &label);

        const BDD_ID &True();

        const BDD_ID &False();

        bool isConstant(BDD_ID f);

        bool isVariable(BDD_ID x);

        BDD_ID topVar(BDD_ID f);

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);

        BDD_ID coFactorTrue(BDD_ID f);

        BDD_ID coFactorFalse(BDD_ID f);

        BDD_ID neg(BDD_ID a);

        BDD_ID and2(BDD_ID a, BDD_ID b);

        BDD_ID or2(BDD_ID a, BDD_ID b);

        BDD_ID xor2(BDD_ID a, BDD_ID b);

        BDD_ID nand2(BDD_ID a, BDD_ID b);

        BDD_ID nor2(BDD_ID a, BDD_ID b);

        BDD_ID xnor2(BDD_ID a, BDD_ID b);

        std::string getTopVarName(const BDD_ID &root);

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

        size_t uniqueTableSize();

        Manager() {//Ctor
            //build bottom node structs
            Node false_node = {0, 0, 0, "False"};
            Node true_node = {1, 1, 1, "True"};
            //insert on unique table
            unique_table.push_back(false_node);
            unique_table.push_back(true_node);
            new_unique_table[{0,0,0}]=0;
            new_unique_table[{1,1,1}]=1;
        }

        ~Manager() {//Dtor

        }
    };
}

#endif
