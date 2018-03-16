//
//  DataManager.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef DataManager_hpp
#define DataManager_hpp
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Definitions.h"
#include "Definitions.h"
#include "DataControler.hpp"

class DataManager
{
    static DataManager *dataManager;
    string directory;
    string clusterFileName;
    int networkSize;
    bool addicionalConstraint;
    int ** relationMatrix;
    string relationMatrixFileName;
    MatrixDataType matrixDataType;
    map<int,vector<int>> epsilon;
    map<pair<int, int>, fitness> E;
    string modelFileName;
    DecisionVariableType decisionVariableType = ILOINTVAR;
    string fileFunctionTable;
    int functionSize;
    bool symmetricProperty = false;    
public:
    int index = 1;
    bool isItNonSymmetricPropertie(string name);
    bool loadPartition = false;
    string upperCase(string str);
    FunctionType getType(string name);
    bool logLevel = false;
    bool builderSet = false;
    bool heuristic = false;
    int clusterUpperBound;
    int clusterLowerBound;
    double executionTime;
    bool datacheck = false;
    DataControler *xSolution;
    void readFunctionTable();
    bool optimizedCode;
    int numRootPartitions;
    map<int,vector<int>> clusterSets;
    string partitionCheck_01;
    string partitionCheck_02;
    string predefinedPartition;
    HeuristicStrategy heuristicStrategy;
    executionSequence sequence;
    static DataManager* getDataManager();
    map<int,map<int,int>> mapping;
    void erase();
    void readBinaryMatrix();
    void loadingRelationMatrix();
    void setDirectory(string directory);
    void setNetworSize(int networkSize);
    void setClusterFileName(string clusterFileName);
    void setLog(bool log);
    void setRelationMatrixFileName(string relationMatrixFileName);
    void setMatrixDataType(MatrixDataType type);
    void setEpsilon(map<int,vector<int>> epsilon);
    void setClusterSets( map<int,vector<int>> clusterSets);
    void setE(map<pair<int, int>, fitness> E);
    void setModelFileName(string modelFileName);
    void setDecisionVariableType(DecisionVariableType type);
    void setAdditionalConstraint(bool addicionalConstraint);
    void getMatrixRelease(vector<FunctionType> &diagonalRelease, vector<FunctionType>&offDiagonalRelease);
    map<int,vector<int>> getEpsilon();
    map<int,vector<int>> getClusterSets();
    map<pair<int, int>, fitness> getE();
    vector<FunctionDetails> functionMapping;
    FunctionDetails FDetails(string name, string release);
    void readRelationMatrixTwo();
    DecisionVariableType getDecisionVariableType();
    
    string getModelFileName();
    string getDirectory();
    string getRelationMatrixFileName();
    string getClusterFileName();
    int ** getRelationMatrix();
    int getNetworSize();
    bool getLog();
    bool getAddicionalConstraint();
    HeuristicStrategy getHeuristicStrategy();
    void setfileFunctionTable(string fileFunctionTable);
    void buildEpsilon();
    string  getModelFileNameSub();
    
};

#endif /* DataManager_hpp */
