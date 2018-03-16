//
//  MultidimensionaIloArray.hpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef MultidimensionaIloArray_hpp
#define MultidimensionaIloArray_hpp

#include <stdio.h>
#include "Definitions.h"

class MultidimensionaIloArray
{
public:
    static IloIntVarArray2 IloIntVarArray2D(const IloEnv env, int n, int lb, int up, string varName);
    static IloIntVarArray IloIntVarArray1D(const IloEnv env, int n, int lb, int up, string varName);
    static IloNumVarArray2 IloNumVarArray2D(const IloEnv env, int n, int lb, int up, string varName);
    static IloNumVarArray IloNumVarArray1D(const IloEnv env, int n, int lb, int up, string varName);
    static IloIntVarArray2 IloIntVarArray2D_WAS(const IloEnv env, int n, int lb, int up, string varName);

    
};
#endif /* MultidimensionaIloArray_hpp */
