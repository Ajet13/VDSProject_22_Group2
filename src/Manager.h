// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H
#include "stdlib.h"
#include "vector"
#include "ManagerInterface.h"

namespace ClassProject {
//using namespace ClassProject;
    class Manager : public ManagerInterface {
    public:
        struct Node{
            BDD_ID node;
            BDD_ID node_high;
            BDD_ID node_low;
            BDD_ID top_var;
            std::string label;
        };
        std::vector<Node> unique_table; //start unique table


        BDD_ID createVar(const std::string &label);
        const BDD_ID &True();
        const BDD_ID &False();

        Manager(){//Ctor
            //build bottom node structs
            Node false_node = {0,0,0,0,"False"};
            Node true_node = {1,1,1,1,"True"};
            //insert on unique table
            unique_table.push_back(false_node);
            unique_table.push_back(true_node);
        }
        ~Manager(){//Dtor

        }
    };
}

#endif
