//
//  PrintManager.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "PrintManager.hpp"
#include "Definitions.h"

using namespace std;

void PrintManager::printPartition(map<int,vector<int>> partition, bool logLevel)
{
    if(logLevel)
    {
        
        for (map<int,vector<int>> ::iterator it = partition.begin();it!= partition.end(); it++)
        {
            cout<<"C"<<it->first<<" = { ";
            for (int i = 0; i<it->second.size(); i++)
            {
                if(i==it->second.size()-1)
                    cout<<it->second.at(i);
                else
                    cout<<it->second.at(i)<<" , ";
            }
            cout<<" }"<<endl;
        }
    }
}

void PrintManager::printMatrixBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    for (int i = 0; i < C1.size(); i++)
    {
        for (int j = 0; j < C2.size(); j++)
            cout << relationMatrix[C1[i]][C2[j]]<<" ";
        cout<<endl;
    }
    
}


void PrintManager::errorHeader(int error)
{
    if(logLevel)
    {
        cout<<endl<<"----------------------------------------------------"<<endl<<endl;
        cout<<"TOTAL ERROR == "<<error<<endl<<endl;
    }
}

void PrintManager::printTime( time_t startTime)
{
    time_t endTime = time(&endTime);
    double currentTime = difftime(endTime, startTime );
    cout<<"ElapsedTime      = "<<currentTime<<" (in seconds)"<<endl;
}


void PrintManager::newLine()
{
    cout<<endl<<endl;
}

void PrintManager::inputData()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"RelationMatrix:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    printRelationMatrix();
}


void PrintManager::printRelationMatrix()
{
    int totalOne=0;
    int sumOneLine =0;
    int sumOneColumn=0;
    int totalOneDiagonal = 0;
    int networkSize = DataManager::getDataManager()->getNetworSize();
    relationMatrix = DataManager::getDataManager()->getRelationMatrix();
    
    for ( int i = 0; i < networkSize; i++ )
    {
        for ( int j = 0; j < networkSize; j++ )
        {
            if (relationMatrix[i][j]==1)
            {
                sumOneLine++;
                totalOne++;
            }
            
            if (relationMatrix[j][i]==1)
            {
                sumOneColumn++;
            }
            
            if (relationMatrix[i][j]==1 && i==j)
            {
                totalOneDiagonal++;
            }
            cout<<" "<<relationMatrix[i][j];
        }
        cout<<" | line = ";
        cout.fill( ' ' );
        cout.width( 5 );
        cout << sumOneLine;
        cout<<" | colum = ";
        cout.fill( ' ' );
        cout.width( 5 );
        cout<<sumOneColumn;
        cout<<endl;
        sumOneLine = 0;
        sumOneColumn = 0;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Aditional information: "<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Number of one's in diagonal   = ["<<totalOneDiagonal<<"]"<<endl;
    cout<<"Number of one's in the matrix = ["<<totalOne<<"]"<<endl;
    cout<<"Matrix size                   = ["<<networkSize<<"]"<<endl;
}


void PrintManager::printEpsilon()
{
    
    cout<<"----------------------------------------------------"<<endl;
    cout<<"epsilon (i): such that i in {0,...,"<<DataManager::getDataManager()->getNetworSize()-1<<"}"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    
    for (int i = 0; i <DataManager::getDataManager()->getNetworSize(); i++)
    {
        cout<<"epsilon ("<< i<<") = { ";
        
        for (int j = 0; j<DataManager::getDataManager()->getEpsilon().at(i).size(); j++)
        {
            if (j!= DataManager::getDataManager()->getEpsilon().at(i).size()-1)
            {
                cout<<DataManager::getDataManager()->getEpsilon().at(i).at(j)<<" , ";
            }
            else
                cout<<DataManager::getDataManager()->getEpsilon().at(i).at(j)<<" ";
        }
        cout<<"}"<<endl;
    }
    cout<<"----------------------------------------------------"<<endl;
    
}

void PrintManager::printAllClusterSet()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<DataManager::getDataManager()->index<<") Cluster Set's:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    for (int i = 0; i <  DataManager::getDataManager()->getClusterSets().size(); ++i)
    {
        cout << "C" << (i) << " = { ";
        
        int size = (int) DataManager::getDataManager()->getClusterSets().at(i).size();
        for (int j = 0; j<size; j++)
        {
            if(j == size-1)
                cout << DataManager::getDataManager()->getClusterSets().at(i).at(j) << " ";
            else
                cout <<DataManager::getDataManager()->getClusterSets().at(i).at(j)<< " , ";
        }
        cout << "} " << endl;
        
        
    }
    
}

void PrintManager::printBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    string strC1 = "\nC" + STR(cluster_k) + " = { ";
    string strC2 = "C" + STR(cluster_l) + " = { ";
    for (int i = 0; i < C1.size(); i++)
    {
        if (i!=C1.size()-1)
            strC1+= STR(C1[i]) + " , ";
        else
            strC1+= STR(C1[i]);
    }
    strC1+=" }";
    for (int j = 0; j < C2.size(); j++)
    {
        if (j!=C2.size()-1)
            strC2+= STR(C2[j]) + " , ";
        else
            strC2+= STR(C2[j]);
    }
    strC2+=" }";
    cout<<strC1<<endl;
    cout<<strC2<<endl;
    
}

void PrintManager::printE()
{
    
    map<pair<int, int>, fitness> aux =  DataManager::getDataManager()->getE();
    map<pair<int, int>, fitness>::iterator it = aux.begin();
    
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Error:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    
    for (;it!= aux.end(); ++it)
    {
        int k1 = it->first.first;
        int k2 = it->first.second;
        cout<<"----------------------------------------------------"<<endl;
        
        cout<< "E("<<k1<< ","<<k2<<") = " <<it->second.error<<endl<<"blocktype = "<<it->second.blockType;
        PrintManager().printBlock(k1, k2, DataManager::getDataManager()->getClusterSets());
        cout<<"Matrix"<<endl;
        PrintManager().printMatrixBlock(k1, k2, DataManager::getDataManager()->getClusterSets());
        cout<<"----------------------------------------------------"<<endl;
        
    }
}

void PrintManager::printCplexResults(bool status, double objValue, double MIPRelativeGap,int nodes, double elapsedTime)
{
    cout<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Resolution information:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Solution status                  = " << status << endl;
    cout<<"Minimal Objective Function Value = " << objValue << endl;
    cout<<"Gap                              = " << MIPRelativeGap<<endl;
    cout<<"Nodes                            = " << nodes <<endl;
    cout<<"Elapsed wall clock time          = " << elapsedTime << " seconds" << endl;
    cout<<"Relation Matrix                  = " << DataManager::getDataManager()->getRelationMatrixFileName() <<endl;
    cout<<"Decision variable type (x,z)     = " << (DataManager::getDataManager()->getDecisionVariableType() == ILOINTVAR ?"IlointVar":"IloNumVar")<<endl;
}



void PrintManager::buildMatrix(map<int, vector<int>> partition)
{
    map<string,clusterGroup> group = buildGroup(partition);
    map<string,clusterGroup>::iterator it = group.begin();
    std::map<string,clusterGroup>::iterator itAux = group.begin();
    int networkSize = DataManager::getDataManager()->getNetworSize();
    string blockMatriz  = "\n   ";
    
    for (it=group.begin(); it!=group.end(); ++it)
    {
        clusterGroup g = it->second;
        
        if (g.size == 0)
            blockMatriz +="E ";
        else
        {
            for (int i = 0; i<g.size; i++)
            {
                blockMatriz +=STR(g.elements[i]);
                
                if (g.size-1==i)
                    blockMatriz+=" ";
            }
        }
    }
    
    blockMatriz+="\n";
    
    for (it=group.begin(); it!=group.end(); ++it)
    {
        clusterGroup g = it->second;
        for (int i = 0; i<g.size; i++)
        {
            itAux = group.begin();
            
            blockMatriz += " " +STR(g.elements[i]);
            
            for(int k = 0; k<partition.size(); k++)
            {
                if (networkSize!=1)
                    blockMatriz+=" ";
                
                clusterGroup gAux = itAux->second;
                
                if (gAux.size ==0)
                    blockMatriz += "-";
                
                for (int l = 0; l<gAux.size; l++)
                {
                    if (networkSize==1 && l == 0)
                        blockMatriz+=" ";
                    
                    blockMatriz += STR(DataManager::getDataManager()->getRelationMatrix()[g.elements[i]][gAux.elements[l]]);
                }
                if (networkSize==1)
                    blockMatriz+="\n";
                itAux++;
            }
            if (g.size-1!=i && networkSize!=1)
                blockMatriz+="\n";
        }
        if (networkSize!=1)
            blockMatriz+="\n\n";
    }
    cout<<blockMatriz;
}



map<string,clusterGroup>  PrintManager::buildGroup(map<int, vector<int>> partition)
{
    map<string,clusterGroup> group;
    
    int networkSize = DataManager::getDataManager()->getNetworSize();
    int i=0;
    for (map<int,vector<int>> ::iterator it = partition.begin();it!= partition.end(); it++)
    {
        string clusterName= "C" + STR(i);
        int *elements = (int *) malloc(networkSize*sizeof(int));
        
        for (int j = 0; j<DataManager::getDataManager()->getClusterSets().at(it->first).size(); j++)
        {
            elements[j] = DataManager::getDataManager()->getClusterSets().at(it->first).at(j);
        }
        clusterGroup g;
        g.elements = elements;
        g.size = (int) DataManager::getDataManager()->getClusterSets().at(it->first).size();
        group.insert(pair<string, clusterGroup>(clusterName,g));
        i++;
    }
    return group;
}

void PrintManager::printSolution(map<int, vector<int>> partition)
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Partition relation matrix:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    PrintManager().buildMatrix(partition);
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Choosen clusters:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    PrintManager().printPartition(partition);
    cout<<"----------------------------------------------------"<<endl;
}


void PrintManager::printFitness(map<int,vector<int>>partition, map<pair<int,int>, MatchingError> imageMatrix, DataControler *d)
{
    
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"DEVIATION MEASURE & IMAGE MATRIX "<<endl;
        cout<<"----------------------------------------------------"<<endl;
        for (int cluster_k = 0; cluster_k<partition.size(); cluster_k++)
        {
            for (int cluster_l = 0; cluster_l<partition.size(); cluster_l++)
            {
                cout<<setw(3)<<imageMatrix.at(make_pair(cluster_k, cluster_l)).blockError<<"+ ";
            }
            cout<<"\t|\t";
            for (int cluster_l = 0; cluster_l<partition.size(); cluster_l++)
            {
                cout<<d->typeToFunction(imageMatrix.at(make_pair(cluster_k, cluster_l)).idealBlockMatching)<<" ";
            }
            cout<<endl;
        }
    }
}


void PrintManager::printMatrixBlock(map<int,vector<int>>partition)
{
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"PARTITION MATRIX "<<endl;
        cout<<"----------------------------------------------------"<<endl;
        
        for (int i = 0; i<partition.size(); i++)
        {
            vector<int> line = partition.at(i);
            if (line.size()!=0)
                cout<<endl;
            else
                line.push_back(-9);
            for (int j = 0 ; j<line.size(); j++)
            {
                if (line[j]==-9) {
                    cout<<setw(2)<<"E"<<"| ";
                }
                else
                    cout<<setw(2)<<line.at(j)<<"| ";
                for (int l = 0; l<partition.size(); l++)
                {
                    vector<int> column = partition.at(l);
                    if (column.size()==0) {
                        cout<<" E ";
                    }
                    for (int k = 0 ; k<column.size(); k++)
                    {
                        if (line[j]==-9)
                            cout<<"__";
                        else
                            cout<<relationMatrix[line[j]][column[k]]<<"+";
                    }
                    if (column.size()!=0)
                        cout<<" ";
                }
                if (line.size()!=0)
                    cout<<endl;
            }
        }
    }
    cout<<endl;
}

void PrintManager::choosenPartition(int partitionNumber, int error, int clusterSize)
{
    //    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<partitionNumber<<") Choosen Partition "<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Error            = "<<error<<endl;
        cout<<"ClusterSize      = "<<clusterSize<<endl;
        
    }
}

void PrintManager::solution(DataControler *d, time_t time)
{
    logLevel = true;
    cout<<endl<<"----------------------------------------------------"<<endl;
    cout<<"FOUND SOLUTION"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"DestiatonMesuare = "<<d->desviation<<endl;
    printTime(time);
    cout<<"----------------------------------------------------"<<endl;
    cout<<"PARTITION         "<<endl;
    cout<<"----------------------------------------------------"<<endl;
    printPartition(d->solution);
    printFitness(d->solution, d->bestfitnness, d);
    printMatrixBlock(d->solution);
}

void PrintManager::printSwap(int clusterA, int nodeA,int clusterB, int nodeB)
{
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Swap:"<<endl;
        cout<<"\t node["<<nodeA<<"] -> cluster["<< clusterB<<"]"<<endl;
        cout<<"\t node["<<nodeB<<"] -> cluster["<< clusterA<<"]";
    }
}

void PrintManager::moveHeader(int partitionNumber, DataControler *d )
{
    // if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<partitionNumber<<") Move"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Error            = "<<d->getMinGlobalError()<<endl;
        cout<<"ClusterSize      = "<<d->initialPartition.size()<<endl;
    }
}

void PrintManager::swapHeader(int partitionNumber, DataControler *d)
{
    // if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<partitionNumber<<") Swap"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Error            = "<<d->getMinGlobalError()<<endl;
        cout<<"ClusterSize      = "<<d->initialPartition.size()<<endl;
    }
}

void PrintManager::printMove(int cluster, int node)
{
    if(logLevel)
    {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"move node "<<node<<" to cluster "<< cluster<<endl;
    }
}

void PrintManager::printError()
{
    map<pair<int, int>, fitness> aux =  DataManager::getDataManager()->getE();
    
    int size = (int) DataManager::getDataManager()->getClusterSets().size();
    
    cout<<"Error:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    
    for (int i  =  0; i< size; i++)
    {
        for (int j = 0; j< size; j++)
        {
            
            cout<< "("<<i<< ","<<j<<") = " <<aux.at(make_pair(i,j)).error<<" ";
        }
        cout<<endl;
    }
//    cout<<"----------------------------------------------------"<<endl;
}

void PrintManager::printVector(vector<int> v, string name)
{
    for (int i = 0; i<v.size(); i++)
    {
        cout<<name<<"["<<v[i]<<"] = "<<1<<endl;
        
    }
}

void PrintManager::printObjectiveValue(float objectiveValue)
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Objective Value = " <<objectiveValue<<endl;
}

void PrintManager::printNewClusterHeader()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"NEW CLUSTER"<<endl;
    cout<<"----------------------------------------------------"<<endl;
}

void PrintManager::printDuals(IloCplex cplex, IloRangeArray lambda, IloRangeArray gamma, IloRangeArray mu)
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Dual variables"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    
    for (int i = 0; i<lambda.getSize(); i++)
        cout<<"Lambda["<<i<<"] = "<<cplex.getDual(lambda[i])<<endl;
    
    for (int i = 0; i<gamma.getSize(); i++)
        cout<<"gamma["<<i<<"] = "<<cplex.getDual(gamma[i])<<endl;
    
    for (int i = 0; i<mu.getSize(); i++)
        cout<<"mu["<<i<<"] = "<< cplex.getDual(mu[i])<<endl;
    
}

void PrintManager::printMasterProblemHeader()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<DataManager::getDataManager()->index<<") MasterProblem"<<endl;
    cout<<"----------------------------------------------------"<<endl;
}

void PrintManager::printReducedCost(IloEnv env, IloIntVarArray x, IloCplex cplex, IloRangeArray lambda, IloRangeArray gamma, IloRangeArray mu)
{
    IloNumArray rcX(env);
    cplex.getReducedCosts(rcX, x);
    
    cout<<"----------------------------------------------------"<<endl;
    cout<< "Reduced Costs"<<endl;
    cout<<"----------------------------------------------------"<<endl;
   
    IloNumArray rcZ(env);
    IloRangeArray  con(env);
    IloNumArray vals(env);
    
    
    cplex.getSlacks(vals, lambda);
    env.out() << "Slacks lambda        = " << vals << endl;
    
    cplex.getSlacks(vals, gamma);
    env.out() << "Slacks gamma         = " << vals << endl;
    
    cplex.getSlacks(vals, mu);
    env.out() << "Slacks mu            = " << vals << endl;
    
    cplex.getValues(vals, x);
    env.out() << "Values x             = " << vals << endl;
    
    cplex.getReducedCosts(vals, x);
    env.out() << "Reduced Costs = " << vals << endl;

}

void PrintManager::printMasterZ( IloCplex cplex, IloIntVarArray2 z)
{
    int n = (int) DataManager::getDataManager()->getClusterSets().size()-1;
    for (int k1 = 0; k1<DataManager::getDataManager()->getClusterSets().size(); k1++)
    {
        for (int k2 = 0; k2<=min(k1,n-1); k2++)
        {
            if (cplex.isExtracted(z[k1][k2]))
            {
                cout<<"z["<<k1<<"]["<<k2<<"]= "<<cplex.getValue(z[k1][k2])<<endl;
            }
        }
    }
}

void PrintManager::printMasterX(IloCplex cplex, IloIntVarArray x)
{
    map<int,vector<int>> auxClusterSets;
    for (int i = 0; i<DataManager::getDataManager()->getClusterSets().size(); i++)
    {
        if (cplex.isExtracted(x[i]))
        {
            cout<<"x["<<i<<"] = "<<cplex.getValue(x[i])<<endl;
            if (cplex.getValue(x[i])>0)
            {
                auxClusterSets.insert(make_pair(i, DataManager::getDataManager()->getClusterSets().at(i)));
            }
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"NEW PARTITION"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    
    printPartition(auxClusterSets, true);
}
void PrintManager::printSubproblemY(IloCplex cplex, IloIntVarArray2 y)
{
    cout<< endl;
    for(int i=0; i <DataManager::getDataManager()->getNetworSize(); i++)
    {
        for(int j=0; j<=min(i,DataManager::getDataManager()->getNetworSize()-1); j++)
        {
            if (cplex.isExtracted(y[i][j]))
            {
                cout<<"y["<<i<<"]["<<j<<"] = "<<cplex.getValue(y[i][j])<<endl;
            }
        }
    }
}

void PrintManager::printSubproblemE(IloCplex cplex, IloNumVar E)
{
    if (cplex.isExtracted(E))
        cout<<"E = "<<cplex.getValue(E)<<endl;
}

void PrintManager::printSubproblemHeader()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<DataManager::getDataManager()->index<<") SubProblem"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    
}
