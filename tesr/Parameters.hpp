//
//  SetParameters.hpp
//  GBlockModeling - current
//
//  Created by Micheli Knechtel on 02/09/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef SetParameters_hpp
#define SetParameters_hpp


#include <stdio.h>
#include "Definitions.h"


class Parameters {
    
    string directory;
    string clusterFileName;
    int networSize;
    bool log = false;
    
public:
    void loadingFromCommandLine(int argc, char **argv);
    void predefinedParameters();
    
    
    void loadInput(string strAux, char **argv, int i);
    void checkInput();
};

#endif /* SetParameters_hpp */
