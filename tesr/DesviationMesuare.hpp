//
//  DesviationMesuare.hpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 20/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef RelationshipDesviationMesuare_hpp
#define RelationshipDesviationMesuare_hpp

#include <stdio.h>
#include <map>
#include "Definitions.h"
#include "BlockError.hpp"

typedef int (BlockError::*ptrFunc)(int,int,map<int,vector<int>>);

class DesviationMesuare {
    map<pair<int, int>, fitness> E;
    vector<ptrFunc>idealBlockSetupVector;
public:
    void loadIdealBlocks();
    DesviationMesuare();
    void calculate();
    void calculateNewClusterError();
};
#endif /* RelationshipDesviationMesuare_hpp */
