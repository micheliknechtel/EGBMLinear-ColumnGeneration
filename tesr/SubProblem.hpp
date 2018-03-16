//
//  SubProblem.hpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 02/08/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef SubProblem_hpp
#define SubProblem_hpp

#include <stdio.h>
#include "Definitions.h"
#include "DataManager.hpp"
#include "MultidimensionaIloArray.hpp"

class SubProblem
{
    IloModel model;
    IloCplex cplex;
    IloEnv env;
    IloIntVarArray x;
    IloIntVarArray2 y;
    IloNumVar E;
   
public:
    SubProblem();
    ~SubProblem();
    void getE();
    IloObjective ReducedCost;
    IloNumArray lambda;
    IloNumArray gamma;
    void criterionFunction();
    void ctr_yij_reinforcement_link();
    void ctr_yij_smaller_xi();
    void errorCompleteBlock();
    void buildModel();
    void exportModel();
    vector<int> getXelements();
    void solve();
    void setDuals(IloNumArray lambda, IloNumArray gamma);
    IloCplex getCplex();
    void getY();
    void printNewCluster();
};
#endif /* SubProblem_hpp */
