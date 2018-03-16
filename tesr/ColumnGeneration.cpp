 //
// ColumnGeneration.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 16/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "ColumnGeneration.hpp"
#include "DataManager.hpp"
#include <time.h>
#include "Definitions.h"
#include "PrintManager.hpp"
#include "MasterProblem.hpp"
#include "SubProblem.hpp"


void ColumnGeneration::solveCplexModel()
{
    bool improve = true;
    try
    {
       
        while (improve)
        {
            PrintManager().printAllClusterSet();
            PrintManager().printEpsilon();
            PrintManager().printError();
            
            MasterProblem *masterProblem = new MasterProblem();
           
            masterProblem->buildModel();
            masterProblem->exportModel();
            masterProblem->solve();
            masterProblem->printReducedCost();
            masterProblem->printDuals();

            SubProblem *subProblem = new SubProblem();
            subProblem->setDuals(masterProblem->getLambdaDuals(), masterProblem->getGammaDuals());
            subProblem->buildModel();
            subProblem->exportModel();
            subProblem->solve();
          
            delete masterProblem;
         
            DataManager::getDataManager()->index++;
        }
    }
    catch (IloException& e)
    {
        cerr << "Error: " << e << endl;
    }
    catch (...)
    {
        cerr << "Unknown exception caught" << endl;
    }
}

