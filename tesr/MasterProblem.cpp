//
//  MasterProblem.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 21/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "MasterProblem.hpp"
#include "DataManager.hpp"
#include "MultidimensionaIloArray.hpp"
#include "PrintManager.hpp"
#include "Definitions.h"
#include <algorithm>


MasterProblem::MasterProblem()
{
    IloModel model(env);
    IloCplex cplex(model);
    IloRangeArray gamma(env);
    IloRangeArray lambda(env);
    IloRangeArray mu(env);
    
    this->model  = model;
    this->cplex  = cplex;
    this->lambda = lambda;
    this->gamma  = gamma;
    this->mu     = mu;
    
    x = MultidimensionaIloArray::IloIntVarArray1D(env, (int) DataManager::getDataManager()->getClusterSets().size(), 0, 1, "x");
    z = MultidimensionaIloArray::IloIntVarArray2D_WAS(env, (int) DataManager::getDataManager()->getClusterSets().size(), 0 , 1, "z");
    
    if (DataManager::getDataManager()->getDecisionVariableType() == ILONUMVAR)
    {
        model.add(IloConversion(env, x, ILOFLOAT));
        for(int i=0; i <(int) DataManager::getDataManager()->getClusterSets().size(); i++)
            model.add(IloConversion(env, z[i], ILOFLOAT));
    }
}

void MasterProblem::buildModel()
{
    criterionFunction();
    ctr_sum_xk1_equals_one();
    ctr_zk1k2_reinforcement_link();
    
    if (DataManager::getDataManager()->getAddicionalConstraint())
        ctr_xk2();
}

void MasterProblem::ctr_sum_xk1_equals_one()
{
    for (int i = 0; i <DataManager::getDataManager()->getNetworSize(); i++)
    {
        IloExpr expr_01(env);
        
        for (int k1 = 0; k1<DataManager::getDataManager()->getEpsilon().at(i).size(); k1++)
        {
            expr_01 += x[DataManager::getDataManager()->getEpsilon().at(i).at(k1)];
        }
        
        lambda.add(expr_01==1);
        expr_01.end();
    }
    lambda.setNames("lambda");
    model.add(lambda);
}

void MasterProblem::ctr_zk1k2_reinforcement_link()
{
    for (int k1 = 0; k1<DataManager::getDataManager()->getClusterSets().size(); k1++)
    {
        int size = (int) DataManager::getDataManager()->getClusterSets().size();
        
        for (int k2 = k1+1; k2<size; k2++)
        {
            mu.add(1>=-z[k2][k1]+x[k1]+x[k2]);
        }
    }
    mu.setNames("mu");
    model.add(mu);
}

void MasterProblem::ctr_xk2()
{
    for (int i = 0; i<DataManager::getDataManager()->getNetworSize(); i++)
    {
        vector<int> notIn;
        
        for (int element = 0; element<DataManager::getDataManager()->getClusterSets().size(); element++)
        {
            if(find(i, element)==false)
            {
                notIn.push_back(element);
            }
        }

        for (int index_k2 = 0; index_k2<notIn.size(); index_k2++)
        {
            int k2 = notIn.at(index_k2);
            
            IloExpr expr_01(env);
            IloExpr expr_02(env);
            
            for (int index_k1 = 0; index_k1<DataManager::getDataManager()->getEpsilon().at(i).size(); index_k1++)
            {
                int k1 = DataManager::getDataManager()->getEpsilon().at(i).at(index_k1);
                
                if (k1<k2)
                {
                    expr_01 += z[k2][k1];
                }
                if (k1>k2)
                {
                    expr_01 += z[k1][k2];
                }
            }
            gamma.add(expr_01 - x[k2] == 0);
            expr_01.end();
        }
    }
    
    gamma.setNames("gamma");
    model.add(gamma);
}

bool MasterProblem::find(int i, int k)
{
    vector<int> v = DataManager::getDataManager()->getEpsilon().at(i);
    vector<int>::iterator it;
    
    it = ::find(v.begin(), v.end(), k);
    if (it !=  v.end())
        return true;
    
    return false;
}

void MasterProblem::criterionFunction()
{
    IloExpr expr_01(env);
    IloExpr expr_02(env);
    
    int size = (int) DataManager::getDataManager()->getClusterSets().size();
    
    for (int k1 = 0; k1<size; k1++)
    {
        int error_k1_k1 = DataManager::getDataManager()->getE().at(make_pair(k1, k1)).error;
        expr_01 += error_k1_k1 * x[k1];
        
        for (int k2 = k1+1; k2<size; k2++)
        {
            int error_k1_k2 = DataManager::getDataManager()->getE().at(make_pair(k1, k2)).error;
            int error_k2_k1 = DataManager::getDataManager()->getE().at(make_pair(k2, k1)).error;
            expr_02 += ( error_k1_k2 + error_k2_k1 ) * z[k2][k1];
        }
    }
    
    IloObjective RollsUsed = IloMinimize(env, expr_01  + expr_02);
    model.add(RollsUsed);
    expr_01.end();
    expr_02.end();
}

void MasterProblem::printDuals()
{
    PrintManager().printDuals(cplex, lambda, gamma, mu);
}

void MasterProblem::getSolution()
{
    vector<int> choosendClusters;
    for (int i = 0; i<DataManager::getDataManager()->getClusterSets().size(); i++)
    {
        if (cplex.isExtracted(x[i]))
            if(cplex.getValue(x[i])>0)
                choosendClusters.push_back(i);
    }
    
    map<int,vector<int>> partition;
    
    for (int i = 0; i<choosendClusters.size(); i++)
    {
        vector<int> v = DataManager::getDataManager()->getClusterSets().at(choosendClusters.at(i));
        partition.insert(make_pair(choosendClusters.at(i), v));
    }
    
    PrintManager().printSolution(partition);
}

void MasterProblem::getZ()
{
    PrintManager().printMasterZ(cplex, z);
}

void MasterProblem::getX()
{
    PrintManager().printMasterX( cplex, x);
}

IloNumArray MasterProblem::getLambdaDuals()
{
    IloNumArray lambdaDuals(env, lambda.getSize());
    
    for (int i = 0; i<lambda.getSize(); i++)
    {
        lambdaDuals[i] = cplex.getDual(lambda[i]);
    }
    return lambdaDuals;
}

IloNumArray MasterProblem::getGammaDuals()
{
    IloNumArray gammaDuals(env, gamma.getSize());
    for (int i = 0; i<gamma.getSize(); i++)
    {
        gammaDuals[i] = cplex.getDual(gamma[i]);
    }
    return gammaDuals;
}

void MasterProblem::exportModel()
{
    string name = DataManager::getDataManager()->getModelFileName() + "_" + STR(DataManager::getDataManager()->index) + ".lp";
    cplex.exportModel(name.c_str());
}

IloCplex MasterProblem::getCplex()
{
    return cplex;
}

IloRangeArray MasterProblem::getGamma()
{
    return gamma;
}

IloRangeArray MasterProblem::getLambda()
{
    return lambda;
}

void MasterProblem::solve()
{
    
    PrintManager().printMasterProblemHeader();
  
    if(!cplex.solve())
    {
        env.error() << "Failed to optimize LP" << endl;
        throw(-1);
    }
    
    if (cplex.getStatus() == IloAlgorithm::Infeasible)
    {
        throw(-1);
    }
    
    PrintManager().printObjectiveValue(cplex.getObjValue());
}

void MasterProblem::printReducedCost()
{
    PrintManager().printReducedCost( env,  x,  cplex,  lambda,  gamma,  mu);
}

MasterProblem::~MasterProblem()
{
    model.end();
    cplex.end();
    x.end();
    z.end();
    gamma.end();
    lambda.end();
    env.end();
}
