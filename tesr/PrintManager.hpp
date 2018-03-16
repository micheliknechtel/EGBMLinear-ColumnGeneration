//
//  PrintManager.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef PrintManager_hpp
#define PrintManager_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "DataManager.hpp"
#include "DataControler.hpp"
using namespace std;

class PrintManager {
    bool logLevel = false;
    int **relationMatrix = DataManager::getDataManager()->getRelationMatrix();
public:
    void printPartition(map<int,vector<int>>partition, bool logLevel = false);
    void printMatrixBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    void printMatrixBlock(map<int,vector<int>>partition);
    void errorHeader(int error);
    void newLine();
    void inputData();
    void printRelationMatrix();
    void printTime( time_t currentTime);
    void printEpsilon();
    void printAllClusterSet();
    void printBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    void printE();
    void printCplexResults(bool status, double objValue, double MIPRelativeGap, int nodes, double elapsedTime);
    void buildMatrix(map<int, vector<int>> partition);
    void printSolution(map<int, vector<int>> partition);
    map<string,clusterGroup> buildGroup(map<int, vector<int>> partition);
    void printFitness(map<int,vector<int>>partition, map<pair<int,int>, MatchingError> imageMatrix, DataControler *d);
    void choosenPartition(int partitionNumber, int error, int clusterSize);
    void solution(DataControler *d, time_t time);
    void moveHeader(int partitionNumber, DataControler *d );
    void printSwap(int clusterA, int nodeA,int clusterB, int nodeB);
    void swapHeader(int partitionNumber, DataControler *d);
    void printMove(int cluster, int node);
    void printError();
    void printNewClusterHeader();
    void printVector(vector<int> v, string name);
    void printObjectiveValue(float objectiveValue);
    void printMasterProblemHeader();
    void printDuals(IloCplex cplex, IloRangeArray lambda, IloRangeArray gamma, IloRangeArray mu);
    void printReducedCost(IloEnv env, IloIntVarArray x, IloCplex cplex, IloRangeArray lambda, IloRangeArray gamma, IloRangeArray mu);
    void printMasterZ( IloCplex cplex, IloIntVarArray2 z);
    void printMasterX(IloCplex cplex, IloIntVarArray x);
    void printSubproblemHeader();
    void printSubproblemY(IloCplex cplex, IloIntVarArray2 y);
    void printSubproblemE(IloCplex cplex, IloNumVar E);
};

#endif /* PrintManager_hpp */
