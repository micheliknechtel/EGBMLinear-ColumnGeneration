//
//  BuilderSet.hpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 18/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef BuilderSet_hpp
#define BuilderSet_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class BuilderSet
{
    int networkSize;
    vector<int> element;
    vector<int> cluster;
    map<int,vector<int>> clusterSets;
    map<int,vector<int>> epsilon;
   public:
    BuilderSet();
    void loadPartitian();
    void buildSet();
    void generateSet();
    void generateSet(int offset, int k);
    void epsilonAddClusterIndex(const vector<int>& v);
    void writeSet(const vector<int>& v);
};
#endif /* BuilderSet_hpp */
