//
//  SubProblem.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 02/08/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "SubProblem.hpp"
#include "DesviationMesuare.hpp"
#include "PrintManager.hpp"


SubProblem::SubProblem()
{
    IloModel model(env);
    IloCplex cplex(model);
    IloNumVar e(env);
    
    this->env   = env;
    this->model = model;
    this->cplex = cplex;
    this->E = e;
    
    x = MultidimensionaIloArray::IloIntVarArray1D(this->env, (int) DataManager::getDataManager()->getNetworSize(), 0 , 1, "x");
    y = MultidimensionaIloArray::IloIntVarArray2D_WAS(this->env, (int) DataManager::getDataManager()->getNetworSize(), 0 , 1, "y");
    
}

void SubProblem::buildModel()
{
    criterionFunction();
    ctr_yij_reinforcement_link();
    ctr_yij_smaller_xi();
    errorCompleteBlock();
}

void SubProblem::solve()
{
    PrintManager().printSubproblemHeader();
    cplex.setOut(env.getNullStream());
    
    //    cplex.setParam(IloCplex::Param::Preprocessing::Aggregator, 0);
    //    cplex.setParam(IloCplex::Param::Preprocessing::Presolve, 0);
    
    if(!cplex.solve())
    {
        env.error() << "Failed to optimize LP" << endl;
        throw(-1);
    }
    
    if(cplex.getValue(ReducedCost)>RC_EPS)
    {
        cout<<"No more possible improvements ..."<<endl;
        throw(-1);
    }
    
    
    map<int,vector<int>> auxClusterSets;
    vector<int> elements = getXelements();
    
    auxClusterSets.insert(make_pair(DataManager::getDataManager()->getClusterSets().size(), elements));
    
    PrintManager().printNewClusterHeader();
    PrintManager().printPartition(auxClusterSets, true);
    PrintManager().printObjectiveValue(cplex.getObjValue());
    
    auxClusterSets.clear();
    
    auxClusterSets = DataManager::getDataManager()->getClusterSets();
    auxClusterSets.insert(make_pair(DataManager::getDataManager()->getClusterSets().size(), elements));
    DataManager::getDataManager()->setClusterSets(auxClusterSets);
    DesviationMesuare().calculate();
    env.end();
    
}

void SubProblem::getE()
{
    PrintManager().printSubproblemE( cplex,E);
    
}
void SubProblem::ctr_yij_reinforcement_link()
{
    IloRangeArray link(env);
    
    for(int i=0; i <DataManager::getDataManager()->getNetworSize(); i++)
    {
        for(int j=0; j<=min(i,DataManager::getDataManager()->getNetworSize()-1); j++)
        {
            link.add(1>=-y[i][j]+x[i]+x[j]);
        }
    }
    link.setNames("link");
    model.add(link);
}

void SubProblem::ctr_yij_smaller_xi()
{
    for(int i=0; i <DataManager::getDataManager()->getNetworSize(); i++)
    {
        for(int j=0; j<=min(i,DataManager::getDataManager()->getNetworSize()-1); j++)
        {
            string name = "y" + STR_P(i) + STR_P(j) + "_smaller_xi" + STR_P(i);
            IloConstraint constraint = (y[i][j]<=x[i] );
            constraint.setName(name.c_str());
            model.add(constraint);
            
            name = "y" + STR_P(i) + STR_P(j) + "_smaller_xj"+STR_P(j);
            IloConstraint constraint_02 = (y[i][j]<=x[j]);
            constraint_02.setName(name.c_str());
            model.add(constraint_02);
        }
    }
}

void SubProblem::criterionFunction()
{
    IloExpr expr_01(env);
    IloExpr expr_02(env);
    IloExpr expr_03(env);
    
    for (int j = 0; j<gamma.getSize(); j++)
    {
        for (int i = 0; i<DataManager::getDataManager()->getNetworSize(); i++)
        {
            expr_03+= gamma[j] * (1 - x[i]);
        }
    }

    for (int i = 0; i<DataManager::getDataManager()->getNetworSize(); i++)
    {
        expr_01+= lambda[i] * x[i];
    }
    
    
    expr_02 = E - expr_01 ;
    ReducedCost = IloMinimize(env,expr_02);
    model.add(ReducedCost);
}


void SubProblem::errorCompleteBlock()
{
    IloExpr expr_01(env);
    
    for(int i=0; i <DataManager::getDataManager()->getNetworSize(); i++)
    {
        for(int j=0; j<=min(i,DataManager::getDataManager()->getNetworSize()-1); j++)
        {
            if (i!=j)
                expr_01+= 2 * ( 2 - DataManager::getDataManager()->getRelationMatrix()[i][j] - DataManager::getDataManager()->getRelationMatrix()[j][i]) * y[i][j];
            else
                expr_01+=  2 * (1-DataManager::getDataManager()->getRelationMatrix()[i][j]) * y[i][j];
        }
    }

    IloConstraint constraint = (E == expr_01 );
    constraint.setName("CompleteBlock");
    model.add(constraint);
    expr_01.end();
}

IloCplex SubProblem::getCplex()
{
    return cplex;
}

void SubProblem::setDuals(IloNumArray lambda, IloNumArray gamma)
{
    this->lambda = lambda;
    this->gamma  = gamma;
}

void SubProblem::exportModel()
{
    string name =  DataManager::getDataManager()->getModelFileNameSub() + "_" + STR(DataManager::getDataManager()->index) + ".lp";
    cplex.exportModel(name.c_str());
}

vector<int> SubProblem::getXelements()
{
    vector<int> elements;
    map<int,vector<int>>auxEpsilon =  DataManager::getDataManager()->getEpsilon();
    
    for (int i = 0; i<DataManager::getDataManager()->getNetworSize(); i++)
    {
        if (cplex.isExtracted(x[i]))
        {
            if (cplex.getValue(x[i])==1)
            {
                elements.push_back(i);
                auxEpsilon.at(i).push_back((int)DataManager::getDataManager()->getClusterSets().size());
            }
        }
    }
    
    if (elements.size()==0)
    {
        cout<<"No more possible improvements ..."<<endl;
        throw -1;
    }
    
    DataManager::getDataManager()->setEpsilon(auxEpsilon);
    return elements;
}

void SubProblem::getY()
{
    PrintManager().printSubproblemY(cplex, y);
}

