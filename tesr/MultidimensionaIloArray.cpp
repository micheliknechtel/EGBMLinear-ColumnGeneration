//
//  MultidimensionaIloArray.cpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "MultidimensionaIloArray.hpp"
#include "DataManager.hpp"

IloIntVarArray2 MultidimensionaIloArray::IloIntVarArray2D(const IloEnv env, int n, int lb, int up, string varName)
{
    IloIntVarArray2 x(env, n);
    for(int i=0; i <n; i++)
    {
        x[i] = IloIntVarArray( env, n);
        for(int j=0; j <n; j++)
        {
            x[i][j] = IloIntVar(env,lb,up);
            string name = varName.c_str()+STR_P(i) +STR_P(j);
            x[i][j].setName(name.c_str());
        }
    }
    return x;
}

IloIntVarArray2 MultidimensionaIloArray::IloIntVarArray2D_WAS(const IloEnv env, int n, int lb, int up, string varName)
{
    IloIntVarArray2 x(env, n);
    for(int i=0; i <n; i++)
    {
        int sum = min(i,n-1)+1;
        x[i] = IloIntVarArray(env, sum);
        
        for(int j=0; j<=min(i,n-1); j++)
        {
            x[i][j] = IloIntVar(env,lb,up);
            string name = varName.c_str()+STR_P(i) +STR_P(j);
            x[i][j].setName(name.c_str());
        }
    }
    return x;
}


IloIntVarArray MultidimensionaIloArray::IloIntVarArray1D(const IloEnv env, int n, int lb, int up, string varName)
{
    IloIntVarArray x(env, n);
    for (int i=0; i < n; i++)
    {
        x[i] = IloIntVar(env,lb,up);
        string name = varName.c_str() + STR_P(i);
        x[i].setName(name.c_str());
    }
    return x;
}



IloNumVarArray2 MultidimensionaIloArray::IloNumVarArray2D(const IloEnv env, int n, int lb, int up, string varName)
{
    IloNumVarArray2 x(env, n);
    for(int i=0; i <n; i++)
    {
        x[i] = IloNumVarArray(env, n);
        for(int j=0; j <n; j++)
        {
            x[i][j] = IloNumVar(env,lb,up);
            string name = varName.c_str()+STR_P(i) +STR_P(j);
            x[i][j].setName(name.c_str());
        }
    }
    return x;
}

IloNumVarArray MultidimensionaIloArray::IloNumVarArray1D(const IloEnv env, int n, int lb, int up, string varName)
{
    IloNumVarArray x(env, n);
    for (int i=0; i < n; i++)
    {
        x[i] = IloNumVar(env,lb,up, ILOINT);
        string name = varName.c_str() + STR_P(i);
        x[i].setName(name.c_str());
    }
    return x;
}
