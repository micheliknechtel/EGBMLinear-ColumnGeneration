//
//  BuilderSet.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 18/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "BuilderSet.hpp"
#include "DataManager.hpp"
#include "PrintManager.hpp"

BuilderSet::BuilderSet()
{
    this->networkSize = DataManager::getDataManager()->getNetworSize();
}

void BuilderSet::buildSet()
{
    if (DataManager::getDataManager()->loadPartition)
        loadPartitian();
    else
        generateSet();
}

void BuilderSet::generateSet()
{
    for (int i =-1; i <networkSize-1; ++i)
    {
        element.push_back(i+1);
        epsilon.insert(make_pair(i+1, vector<int>()));
    }
    
    for (int i = 0; i <networkSize; ++i)
    {
        generateSet(0, i);
    }
    
    epsilonAddClusterIndex(element);
    DataManager::getDataManager()->setClusterSets(clusterSets);
    DataManager::getDataManager()->setEpsilon(epsilon);
}


void BuilderSet::epsilonAddClusterIndex(const vector<int>& v)
{
    static int count = 0;
    clusterSets.insert(make_pair(count, v));
    
    for (int i = 0; i<v.size(); i++)
    {
        epsilon.at(v[i]).push_back(count);
    }
    ++count;
}

void BuilderSet::loadPartitian()
{
    string str = DataManager::getDataManager()->getDirectory() +  DataManager::getDataManager()->predefinedPartition;
    const char * fin  = str.c_str();
    int clusterIndex = 0;
    vector<int> v;
    ifstream file(fin);

    clusterSets.clear();
    epsilon.clear();
    
    for (int i =0; i <networkSize; ++i)
    {
        epsilon.insert(make_pair(i, vector<int>()));
    }
    
    while (!(file.eof() || file.fail()))
    {
        string buffer;
        file>>buffer;
        
        size_t found = buffer.find('C');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('=');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('{');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find(',');
        if (found!=std::string::npos)
            continue;
        
        found = buffer.find('}');
        if (found!=std::string::npos)
        {
            clusterSets.insert(pair<int, vector<int>>(clusterIndex,v));
            
            for (int j = 0; j<v.size(); j++)
                epsilon.at(v[j]).push_back(clusterIndex);
            v.clear();
            clusterIndex++;
            continue;
            
        }
        int node = atoi(buffer.c_str());
        v.push_back(node);
     
    }
    

    DataManager::getDataManager()->setClusterSets(clusterSets);
    DataManager::getDataManager()->setEpsilon(epsilon);
}
void BuilderSet::generateSet(int offset, int k)
{
    if (k == 0 && offset == 0 )
        return;
    
    if (k == 0)
    {
        epsilonAddClusterIndex(cluster);
        return;
    }
    
    for (int i = offset; i <= element.size() - k; ++i)
    {
        cluster.push_back(element[i]);
        generateSet(i+1, k-1);
        cluster.pop_back();
    }
}
