//
//  CPUScheduler.hpp
//  OperatingSystems
//
//  Created by Anwar Kadirov on 5/10/18.
//  Copyright © 2018 Anwar Kadirov. All rights reserved.
//

#ifndef CPUScheduler_hpp
#define CPUScheduler_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include "Process.h"
using namespace std;

class CPUScheduler{
public:
    CPUScheduler();
    void InsertLevelNew(Process, int lvl);
    void ShowProcesses();
    bool isEmpty();
    void MoveToCPU(vector<Process> &);
    void SetLvl(int);
    void InsertLevelPreempt(Process, int lvl);
    
    
private:
    vector <Process> Level;
};
#endif /* CPUScheduler_hpp */
