//
//  DesviationMesuare.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 20/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "DesviationMesuare.hpp"
#include "DataManager.hpp"
#include "BlockError.hpp"
#include "PrintManager.hpp"

DesviationMesuare::DesviationMesuare()
{
    loadIdealBlocks();
}

void DesviationMesuare::calculate()
{
    
    map<int,vector<int>>::iterator k1  = DataManager::getDataManager()->clusterSets.begin();
    
    for (k1  = DataManager::getDataManager()->clusterSets.begin(); k1!= DataManager::getDataManager()->clusterSets.end(); ++k1)
    {
        map<int,vector<int>>::iterator k2  = DataManager::getDataManager()->clusterSets.begin();
        
        for (k2  = DataManager::getDataManager()->clusterSets.begin(); k2!= DataManager::getDataManager()->clusterSets.end();++k2)
        {
            int size_k1 = (int) k1->second.size();
            int size_k2 = (int) k2->second.size();
            
            int error = size_k1 * size_k2;
            fitness fit;
            
            if (k1->first == k2->first)
            {
                error = (BlockError().*idealBlockSetupVector.at(0))(k1->first, k2->first, DataManager::getDataManager()->getClusterSets());
                fit.error = error;
                fit.blockType = 0;
            }
            else
            {
                error = (BlockError().*idealBlockSetupVector.at(1))(k1->first, k2->first, DataManager::getDataManager()->getClusterSets());
                fit.error = error;
                fit.blockType = 1;
            }
            E.insert(make_pair(pair<int, int>(k1->first, k2->first),fit));
        }
    }
    DataManager::getDataManager()->setE(E);
}

void DesviationMesuare::calculateNewClusterError()
{
    
    map<int,vector<int>>::iterator k1  = DataManager::getDataManager()->clusterSets.end();
    map<int,vector<int>>::iterator k2  = DataManager::getDataManager()->clusterSets.begin();
    
    E = DataManager::getDataManager()->getE();
    
    for (k2  = DataManager::getDataManager()->clusterSets.begin(); k2!= DataManager::getDataManager()->clusterSets.end();++k2)
    {
        int size_k1 = (int) k1->second.size();
        int size_k2 = (int) k2->second.size();
        
        int error = size_k1 * size_k2;
        fitness fit;
        
        if (k1->first == k2->first)
        {
            error = (BlockError().*idealBlockSetupVector.at(0))(k1->first, k2->first, DataManager::getDataManager()->getClusterSets());
            fit.error = error;
            fit.blockType = 0;
        }
        else
        {
            error = (BlockError().*idealBlockSetupVector.at(1))(k1->first, k2->first, DataManager::getDataManager()->getClusterSets());
            fit.error = error;
            fit.blockType = 1;
        }
        E.insert(make_pair(pair<int, int>(k1->first, k2->first),fit));
    }
    
    
    
    
    DataManager::getDataManager()->setE(E);
}


void DesviationMesuare::loadIdealBlocks()
{
    idealBlockSetupVector.push_back(&BlockError::completeBlock);
    idealBlockSetupVector.push_back(&BlockError::nullBlock);
    
    //    idealBlockSetupVector.push_back(&BlockError::rowDominant);
    //    idealBlockSetupVector.push_back(&BlockError::colDominant);
    //    idealBlockSetupVector.push_back(&BlockError::colFunctional);
    //    idealBlockSetupVector.push_back(&BlockError::rowFunctional);
    //    idealBlockSetupVector.push_back(&BlockError::rowRegular);
    //    idealBlockSetupVector.push_back(&BlockError::colRegular);
    //    idealBlockSetupVector.push_back(&BlockError::regularBlock);
}



