//
//  SetParameters.cpp
//  GBlockModeling - current
//
//  Created by Micheli Knechtel on 02/09/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Parameters.hpp"
#include "DataManager.hpp"
#include "PrintManager.hpp"

void Parameters::loadingFromCommandLine(int argc, char **argv)
{
    for (int i = 0; i<argc; i++)
    {
        string strAux = argv[i];
        loadInput(strAux, argv, i);
    }
    
    checkInput();
    
}

void Parameters::loadInput(string strAux, char **argv, int i)
{
    if (strAux.compare("-directory")==0)
        directory = argv[++i];
   
    if (strAux.compare("-clusterFileName")==0)
        clusterFileName = argv[++i];
    
    if (strAux.compare("-networkSize")==0)
        networSize = atoi(argv[++i]);
}


void Parameters::checkInput()
{
    if (directory.compare("")==0)
    {
        cout << "Error: -directory not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->setDirectory(directory);
}

void Parameters::predefinedParameters()
{
    // Shared Parameter's
    DataManager::getDataManager()->setDirectory("/Users/micheliknechtel/Documents/xCode/GGBMCG/");
    DataManager::getDataManager()->setClusterFileName("clusterSet.dat");
    DataManager::getDataManager()->setModelFileName("masterModel");
   
    // CGModel Parameter's
    DataManager::getDataManager()->setDecisionVariableType(ILOINTVAR);
    DataManager::getDataManager()->setDecisionVariableType(ILONUMVAR);
    DataManager::getDataManager()->setAdditionalConstraint(true);
    DataManager::getDataManager()->setRelationMatrixFileName("tesr/networks/binary/NW_RD_05");
    DataManager::getDataManager()->setMatrixDataType(BINARY);

    // BuilderSet Parameter's
    DataManager::getDataManager()->builderSet = false;
    DataManager::getDataManager()->loadPartition = false;
    
    // Heuristic Parameter's
    DataManager::getDataManager()->predefinedPartition = "tesr/predefinedPartions/predefinedPartition_01";
    DataManager::getDataManager()->partitionCheck_01 = "partitionCheck_01";
    DataManager::getDataManager()->partitionCheck_02 = "partitionCheck_02";
    DataManager::getDataManager()->setfileFunctionTable("tesr/idealBlock/FM_06");

    // Just Loading ...
    DataManager::getDataManager()->loadingRelationMatrix();
    
    DataManager::getDataManager()->heuristic = true;
    DataManager::getDataManager()->executionTime = 3600;
    DataManager::getDataManager()->sequence = RANDOM;
    DataManager::getDataManager()->logLevel = true;
    DataManager::getDataManager()->optimizedCode = false;
    DataManager::getDataManager()->datacheck = false;
    DataManager::getDataManager()->heuristicStrategy = FIRST_EQUAL_OR_BEST_SOLUTION;
    DataManager::getDataManager()->numRootPartitions = DataManager::getDataManager()->getNetworSize();
    
    
  
    PrintManager().inputData();
}


