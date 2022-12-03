// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

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
        BDD_ID createVar(const std::string &label);
        const BDD_ID &True();
        const BDD_ID &False();

        Manager(){//Ctor
            //Node first_node = {0,0,0,0,"label"};
        }
        ~Manager(){//Dtor

        }
    };
}

#endif
