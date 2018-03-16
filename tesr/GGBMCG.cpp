//
//  GGBMCG.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 17/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "GGBMCG.hpp"
#include <stdio.h>
#include <string.h>
#include "Definitions.h"
#include "Parameters.hpp"
#include "BuilderSet.hpp"
#include "DesviationMesuare.hpp"
#include "PrintManager.hpp"
#include "ColumnGeneration.hpp"
#include "VNSHeuristic.hpp"
#include <vector>

vector<int> randomSup;


int main (int argc, char **argv)
{
    Parameters * parameters = new Parameters();
    parameters->predefinedParameters();
    
    if(DataManager::getDataManager()->builderSet)
    {
        BuilderSet *clusterSet = new BuilderSet();
        clusterSet->buildSet();
    }

    if(DataManager::getDataManager()->heuristic)
    {
        VNSHeuristic *vnsHeuristic = new VNSHeuristic();
        vnsHeuristic->runVNSHeuristic();
    }

    DesviationMesuare * desviationMesuare = new  DesviationMesuare();
    desviationMesuare->calculate();

    ColumnGeneration *columnGeneration = new ColumnGeneration();
    columnGeneration->solveCplexModel();
}



