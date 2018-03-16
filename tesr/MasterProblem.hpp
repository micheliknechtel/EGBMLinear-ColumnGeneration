//
//  MasterProblem.hpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 21/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef MasterProblem_hpp
#define MasterProblem_hpp
#include "Definitions.h"
#include <stdio.h>
#include <map>

class MasterProblem {
    IloModel model;
    IloEnv env;
    IloCplex cplex;
    IloIntVarArray x;
    IloIntVarArray2 z;
    IloRangeArray gamma;
    IloRangeArray lambda;
    IloRangeArray mu;
public:
    ~MasterProblem();
    MasterProblem();
    void criterionFunction();
    void ctr_sum_xk1_equals_one();
    void ctr_zk1k2_equals_and_bigger_than_zero();
    void ctr_zk1k2_reinforcement_link();
    void ctr_xk2();
    void buildModel();
    void getSolution();
    void printReducedCost();
    void getZ();
    void getX();
    void exportModel();
    void printDuals();
    void print();
    void solve();
    bool find(int i, int k);
    IloRangeArray getLambda();
    IloRangeArray getGamma();
    IloNumArray getLambdaDuals();
    IloNumArray getGammaDuals();
    IloCplex getCplex();
};
#endif /* MasterProblem_hpp */
