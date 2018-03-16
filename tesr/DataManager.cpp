//
//  DataManager.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "DataManager.hpp"
#include <cstring>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "PrintManager.hpp"

DataManager* DataManager::dataManager = NULL;

DataManager* DataManager::getDataManager()
{
    if(!dataManager)
    {
        dataManager = new DataManager;
    }
    return dataManager;
}

void DataManager::setDirectory(string directory)
{
    this->directory = directory;
}

void DataManager::setNetworSize(int networkSize)
{
    this->networkSize = networkSize;
}

void DataManager::setClusterFileName(string clusterFileName)
{
    this->clusterFileName = clusterFileName;
}

void DataManager::setLog(bool log)
{
    this->logLevel = log;
}

int DataManager::getNetworSize()
{
    return networkSize;
}

string DataManager::getRelationMatrixFileName()
{
    return directory + relationMatrixFileName;
}

string  DataManager::getModelFileName()
{
     return directory+"/model/"+ modelFileName;
}

string  DataManager::getModelFileNameSub()
{
    return directory +"/model/"+ "subModel";
}
void DataManager::setModelFileName(string modelFileName)
{
    this->modelFileName = modelFileName;
}

void DataManager::readBinaryMatrix()
{
    string str = directory + relationMatrixFileName;
    const char * fin  = str.c_str();
    
    ifstream file(fin);
    
    if (file.is_open())
    {
        file>>networkSize;
        
        relationMatrix =  new int*[networkSize];
        
        for ( int i = 0; i < networkSize; i++ )
        {
            relationMatrix[i] =  new int[networkSize];
            
            for ( int j = 0; j < networkSize; j++ )
            {
                file>>relationMatrix[i][j];
            }
        }

    }
    else
    {
        cout<<"Could not find file "<<str;
        exit(1);
    }
    
}

void DataManager::setRelationMatrixFileName(string relationMatrixFileName)
{
    this->relationMatrixFileName = relationMatrixFileName;
}

void DataManager::loadingRelationMatrix()
{
    if(matrixDataType == BINARY)
        readBinaryMatrix();
    else if(matrixDataType == EDGES)
        readRelationMatrixTwo();
  
    readFunctionTable();

}

void DataManager::readRelationMatrixTwo()
{
    string str = directory + relationMatrixFileName;
    const char * fin  = str.c_str();
    ifstream file(fin);
    
    
    int l, m;
    file>>networkSize;
    
    relationMatrix =  new int*[networkSize];
    
    for ( int i = 0; i < networkSize; i++ )
    {
        relationMatrix[i] =  new int[networkSize];
        
        for ( int j = 0; j < networkSize; j++ )
        {
            relationMatrix[i][j] = 0;
        }
    }
    
    while(1)
    {
        if(file.eof())
        {
            break;
        }
        file>>l>>m;
        relationMatrix[l-1][m-1] = 1;
    }
}

void DataManager::readFunctionTable()
{
    string str = directory + fileFunctionTable;
    const char * fin  = str.c_str();
    ifstream file(fin);
    
    for ( int i  = 0; !file.eof(); i++ )
    {
        string name, release;
        
        file>>name>>release;
        
        if (name.compare("")==0 && release.compare("")==0)
        {
            continue;
        }
        
        FunctionDetails fDetails = FDetails(name, release);
        functionMapping.push_back(fDetails);
        functionSize = i+1;
        
        if (!symmetricProperty)
        {
            symmetricProperty = isItNonSymmetricPropertie(name);
        }
        
        if (name.compare("ALL_FUNCTIONS") == 0)
        {
            functionMapping.clear();
            
            for (itFunctionType)
            {
                if (it != ALL_FUNCTIONS)
                {
                    FunctionDetails fDetails = FDetails(fTypeMapping[it], release);
                    functionMapping.push_back(fDetails);
                }
            }
            
            FunctionDetails fDetails = FDetails(fTypeMapping[ALL_FUNCTIONS], release);
            functionMapping.push_back(fDetails);
            functionSize = 17;
            break;
        }
    }
}

FunctionType DataManager::getType(string name)
{
    if ((strcmp(name.c_str(), fTypeMapping[NBDO])==0))
        return NBDO;
    else if ((strcmp(name.c_str(), fTypeMapping[NBDZ])==0))
        return NBDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[NBWD])==0))
        return NBWD;
    else if ((strcmp(name.c_str(), fTypeMapping[CBDO])==0))
        return CBDO;
    else if ((strcmp(name.c_str(), fTypeMapping[CBDZ])==0))
        return CBDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[CBWD])==0))
        return CBWD;
    else if ((strcmp(name.c_str(), fTypeMapping[ALL_FUNCTIONS])==0))
        return ALL_FUNCTIONS;
    else if ((strcmp(name.c_str(), fTypeMapping[RRB])==0))
        return RRB;
    else if ((strcmp(name.c_str(), fTypeMapping[CRB])==0))
        return CRB;
    else if ((strcmp(name.c_str(), fTypeMapping[RB])==0))
        return RB;
    else if ((strcmp(name.c_str(), fTypeMapping[RDWD])==0))
        return RDWD;
    else if ((strcmp(name.c_str(), fTypeMapping[RDDO])==0))
        return RDDO;
    else if ((strcmp(name.c_str(), fTypeMapping[RDDZ])==0))
        return RDDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[CDWD])==0))
        return CDWD;
    else if ((strcmp(name.c_str(), fTypeMapping[CDDO])==0))
        return CDDO;
    else if ((strcmp(name.c_str(), fTypeMapping[CDDZ])==0))
        return CDDZ;
    else if ((strcmp(name.c_str(), fTypeMapping[CF])==0))
        return CF;
    else if ((strcmp(name.c_str(), fTypeMapping[RF])==0))
        return RF;
    else
        throw -1;// type does not exist!
}


FunctionDetails DataManager::FDetails(string name, string release)
{
    release = upperCase(release);
    FunctionRelease funcRelease = (strcmp(release.c_str(), "ALL")==0) ? ALL:(strcmp(release.c_str(), "OFF_DIAGONAL")==0)? OFF_DIAGONAL : DIAGONAL;
    FunctionDetails fDetails;
    fDetails.name = name;
    fDetails.release = funcRelease;
    fDetails.type = getType(name);
    fDetails.symmetricProperty = !isItNonSymmetricPropertie(name);
    return fDetails;
}

bool DataManager::isItNonSymmetricPropertie(string name)
{
    if ("RRB" == name)
        return true;
    if ("CRB" == name)
        return true;
    if ("RDWD" == name)
        return true;
    if ("RDDZ" == name)
        return true;
    if ("RDDO" == name)
        return true;
    if ("CDWD" == name)
        return true;
    if ("CDDO" == name)
        return true;
    if ("CDDZ" == name)
        return true;
    if ("CF" == name)
        return true;
    if ("RF" == name)
        return true;
    
    return false;
}

string DataManager::upperCase(string str)
{
    int i=0;
    while (str[i])
    {
        str[i]= (toupper(str[i]));
        i++;
    }
    return str;
}


void DataManager::setMatrixDataType(MatrixDataType type)
{
    matrixDataType = type;
}

int ** DataManager::getRelationMatrix()
{
    return relationMatrix;
    
}

void DataManager::setEpsilon(map<int,vector<int>> epsilon)
{
    this->epsilon = epsilon;
}

map<int,vector<int>> DataManager::getEpsilon()
{
    return this->epsilon;
}

void DataManager::setClusterSets(map<int,vector<int>> clusterSets)
{
    this->clusterSets = clusterSets;
}

map<int,vector<int>> DataManager::getClusterSets()
{
    return this->clusterSets;
}


void  DataManager::setE(map<pair<int, int>, fitness> E)
{
    this->E = E;
}

map<pair<int, int>, fitness>  DataManager::getE()
{
    return this->E;
}

void  DataManager::setDecisionVariableType(DecisionVariableType type)
{
    this->decisionVariableType = type;
}

DecisionVariableType  DataManager::getDecisionVariableType()
{
    return decisionVariableType;
}

bool DataManager::getAddicionalConstraint()
{
    return addicionalConstraint;
}

void DataManager::setAdditionalConstraint(bool addicionalConstraint)
{
    this->addicionalConstraint = addicionalConstraint;
}

void DataManager::erase()
{
    map<int,vector<int>>::iterator it;
    it = clusterSets.find(12);
    clusterSets.erase (it);
}

HeuristicStrategy DataManager::getHeuristicStrategy()
{
    return  heuristicStrategy;
}

void DataManager::getMatrixRelease(vector<FunctionType> &diagonalRelease, vector<FunctionType>&offDiagonalRelease)
{
    
    for (int i = 0 ; i<functionMapping.size(); i++)
    {
        if (functionMapping[i].release == DIAGONAL || functionMapping[i].release == ALL)
            diagonalRelease.push_back(functionMapping[i].type);
        
        if (functionMapping[i].release == OFF_DIAGONAL || functionMapping[i].release == ALL)
            offDiagonalRelease.push_back(functionMapping[i].type);
    }
}

string DataManager::getDirectory()
{
    return directory;
}

void DataManager::setfileFunctionTable(string fileFunctionTable)
{
    this->fileFunctionTable = fileFunctionTable;
}

void DataManager::buildEpsilon()
{
    
    map<int,vector<int>>::iterator it  = clusterSets.begin();
    epsilon.clear();
    if (clusterSets.size() == 1)
    {
        vector<int> v;
        v.push_back(0);
         for (int i = 0; i<networkSize; i++)
             epsilon.insert(make_pair(i, v));
        return;
    }
    
    for (int i = 0; i<networkSize; i++)
        epsilon.insert(make_pair(i, vector<int>()));
    
    for (it  = clusterSets.begin(); it!= clusterSets.end(); ++it)
    {
        for (int i = 0; i<it->second.size(); i++)
        {
            epsilon.at(it->second[i]).push_back(it->first);
        }
    }

};
