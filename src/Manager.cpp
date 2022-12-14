#include "Manager.h"
#include "algorithm"
#include "iostream"

using namespace ClassProject;

/**
 * Create a ne variable
 *
 * @param label String text representation of variable.
 * @return ID of variable or place in unique table.
 */
BDD_ID Manager::createVar(const std::string &label) {
    for (auto iter: unique_table) {
        if (iter.label == label) {
            return iter.top_var;
        }
    }
    unique_table.push_back({1, 0, unique_table.size(), label});
    return unique_table.size() - 1;
}

/**
 * True node
 *
 * @param none.
 * @return ID of true node or place in unique table.
 */
const BDD_ID &Manager::True() {
    return unique_table[1].top_var;
}

/**
 * False node
 *
 * @param none.
 * @return ID of False node or place in unique table.
 */
const BDD_ID &Manager::False() {
    return unique_table[0].top_var;
}

/**
 * Check if BDD node is constant
 *
 * @param BDD ID to check.
 * @return True if constant.
 */
bool Manager::isConstant(BDD_ID f) {
    return unique_table[f].node_high == unique_table[f].node_low;
}

/**
 * Check if BDD node is variable
 *
 * @param BDD ID of node to be checked.
 * @return True if Variable.
 */
bool Manager::isVariable(BDD_ID x) {
    return unique_table[x].node_high == True() && unique_table[x].node_low == False();
}

/**
 * Top Variable of a BDD
 *
 * @param BDD ID of node to be checked.
 * @return ID of node that represents the variable.
 */
BDD_ID Manager::topVar(BDD_ID f) {
    return unique_table[f].top_var;
}
/**
 * IF THEN ELSE operator
 *
 * @param i, t, e as BDD IDs of nodes on whom to perform the operation.
 * @return ID of node that represents the new simplified BDD tree.
 */
BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e) {
    if (i == True()) return t;
    if (i == False()) return e;
    if (t == e) return t;
    if (t == True() & e == False()) return i;
    for (auto iter: computed_table) {
        if (iter.i == i & iter.e == e & iter.t == t) return (iter.r);
    }
    BDD_ID top_variable = isConstant(t) ? topVar(i) : std::min(topVar(i), topVar(t));
    BDD_ID top_variable2 = isConstant(e) ? topVar(i) : std::min(topVar(i), topVar(e));
    top_variable = std::min(top_variable, top_variable2);
    BDD_ID r_high = ite(coFactorTrue(i, top_variable), coFactorTrue(t, top_variable), coFactorTrue(e, top_variable));
    BDD_ID r_low = ite(coFactorFalse(i, top_variable), coFactorFalse(t, top_variable), coFactorFalse(e, top_variable));
    if (r_high == r_low) return r_high;
    BDD_ID count = 0;
    bool found = false;
    for (auto iter: unique_table) {
        if (iter.top_var == top_variable & iter.node_high == r_high & iter.node_low == r_low) {
            found = true;
            break;
        }
        count++;
    }
    if (!found) {
        unique_table.push_back({r_high, r_low, top_variable});
        count = uniqueTableSize() - 1; //to be reviewed
    }
    computed_table.push_back({i, t, e, count});
    return count;
}

/**
 * Cofactor with respect to a variable or constant evaluated as true
 *
 * @param f, x as BDD ID of function to be factored and as variable to factor from.
 * @return ID of node that represents the factored expression.
 */
BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x) {
    if (isConstant(f) || isConstant(x) || unique_table[f].top_var > x) return f;
    if (unique_table[f].top_var == x) return unique_table[f].node_high;
    else if (unique_table[f].top_var < x) {
        BDD_ID T = coFactorTrue(unique_table[f].node_high, x);
        BDD_ID F = coFactorTrue(unique_table[f].node_low, x);
        return ite(unique_table[f].top_var, T, F);
    }
}

/**
 * Cofactor with respect to a variable or constant evaluated as false
 *
 * @param f, x as BDD ID of function to be factored and as variable to factor from.
 * @return ID of node that represents the factored expression.
 */
BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x) {
    if (isConstant(f) || isConstant(x) || unique_table[f].top_var > x) return f;
    if (unique_table[f].top_var == x) return unique_table[f].node_low;
    else if (unique_table[f].top_var < x) {
        BDD_ID T = coFactorFalse(unique_table[f].node_high, x);
        BDD_ID F = coFactorFalse(unique_table[f].node_low, x);
        return ite(unique_table[f].top_var, T, F);
    }
}

/**
 * Cofactor with respect to its top variable evaluated as true
 *
 * @param f as BDD ID of function to be factored.
 * @return ID of node that represents the factored expression.
 */
BDD_ID Manager::coFactorTrue(BDD_ID f) {
    return coFactorTrue(f, unique_table[f].top_var);
}

/**
 * Cofactor with respect to its top variable evaluated as false
 *
 * @param f as BDD ID of function to be factored.
 * @return ID of node that represents the factored expression.
 */
BDD_ID Manager::coFactorFalse(BDD_ID f) {
    return coFactorFalse(f, unique_table[f].top_var);
}

/**
 * Negate a BDD tree or node
 *
 * @param a as BDD ID of function to be negated.
 * @return ID of node that represents the negated expression.
 */
BDD_ID Manager::neg(BDD_ID a) {
    BDD_ID out = ite(a, 0, 1);
    if (std::empty(unique_table[out].label))unique_table[out].label = "~" + unique_table[a].label; //questionable
    return out;
}

/**
 * Logic and of two BDD trees or nodes
 *
 * @param a, b as BDD IDs of the functions to be logic and(ed).
 * @return ID of node that represents the expression.
 */
BDD_ID Manager::and2(BDD_ID a, BDD_ID b) {
    BDD_ID out = ite(a, b, 0);
    if (std::empty(unique_table[out].label))
        unique_table[out].label = unique_table[a].label + "&" + unique_table[b].label; //questionable
    return out;
}

/**
 * Logic or of two BDD trees or nodes
 *
 * @param a, b as BDD IDs of the functions to be logic or(ed).
 * @return ID of node that represents the expression.
 */
BDD_ID Manager::or2(BDD_ID a, BDD_ID b) {
    BDD_ID out = ite(a, 1, b);
    if (std::empty(unique_table[out].label))
        unique_table[out].label = unique_table[a].label + "+" + unique_table[b].label; //questionable
    return out;
}

/**
 * Logic xor of two BDD trees or nodes
 *
 * @param a, b as BDD IDs of the functions to be logic xor(ed).
 * @return ID of node that represents the expression.
 */
BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) {
    BDD_ID out = ite(a, neg(b), b);
    if (std::empty(unique_table[out].label))
        unique_table[out].label = unique_table[a].label + "⊕" + unique_table[b].label; //questionable
    return out;
}

/**
 * Logic nand of two BDD trees or nodes
 *
 * @param a, b as BDD IDs of the functions to be logic nand(ed).
 * @return ID of node that represents the expression.
 */
BDD_ID Manager::nand2(BDD_ID a, BDD_ID b) {
    BDD_ID out = ite(a, neg(b), 1);
    if (std::empty(unique_table[out].label))
        unique_table[out].label = unique_table[a].label + "‾" + unique_table[b].label; //questionable
    return out;
}

/**
 * Logic nor of two BDD trees or nodes
 *
 * @param a, b as BDD IDs of the functions to be logic nor(ed).
 * @return ID of node that represents the expression.
 */
BDD_ID Manager::nor2(BDD_ID a, BDD_ID b) {
    BDD_ID out = ite(a, 0, neg(b));
    if (std::empty(unique_table[out].label))
        unique_table[out].label = unique_table[a].label + "∓" + unique_table[b].label; //questionable
    return out;
}

/**
 * Logic xnor of two BDD trees or nodes
 *
 * @param a, b as BDD IDs of the functions to be logic xnor(ed).
 * @return ID of node that represents the expression.
 */
BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) {
    BDD_ID out = ite(a, b, neg(b));
    if (std::empty(unique_table[out].label))
        unique_table[out].label = unique_table[a].label + "⊙" + unique_table[b].label; //questionable
    return out;
}

/**
 * Get top variable label
 *
 * @param root node of the tree to get label of.
 * @return string text of the label.
 */
std::string Manager::getTopVarName(const BDD_ID &root) {
    return unique_table[topVar(root)].label;
}

/**
 * Find all notes when traversing the tree
 *
 * @param root, nodes_of_root as BDD id of the tree and the set to contain all nodes.
 * @return none.
 */
void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    nodes_of_root.insert(root);
    if (!isConstant(root)) {
        findNodes(coFactorTrue(root), nodes_of_root);
        findNodes(coFactorFalse(root), nodes_of_root);
    }
}

/**
 * Find variables of a tree
 *
 * @param root, vars_of_root as BDD id of the tree to be checked and, the set to contain variables.
 * @return none.
 */
void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
    std::set<BDD_ID> NOF;
    findNodes(root, NOF);
    for (auto iter: NOF) if (!isConstant(iter)) vars_of_root.insert(topVar(iter));
}

/**
 * Size of Unique Table
 *
 * @param none.
 * @return integer size of the table.
 */
size_t Manager::uniqueTableSize() {
    return unique_table.size();
}