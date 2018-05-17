//
//  CPUScheduler.cpp
//  OperatingSystems
//
//  Created by Anwar Kadirov on 5/10/18.
//  Copyright © 2018 Anwar Kadirov. All rights reserved.
//

#include "CPUScheduler.hpp"
#include <iostream>
#include <vector>
using namespace std;

CPUScheduler::CPUScheduler()
{
    
}
void CPUScheduler::InsertLevelNew(Process proc, int lvl)
{
    proc.SetCurrentLevel(lvl);
    Level.push_back(proc);
}

bool CPUScheduler::isEmpty()
{
    return Level.empty();
}
void CPUScheduler::ShowProcesses()
{
    if(isEmpty())
    {
        cout << "EMPTY" << endl;
    }
    else{
        int position = 1;
        for (int y=0;y<Level.size();y++)
        {
            cout << position << ") PID: " << Level[y].GetPID() << endl;
            position++;
            
        }
    }

}
void CPUScheduler::MoveToCPU(vector <Process> &CPUobj)
{
    CPUobj[0] = Level[0];
    Level.erase(Level.begin());
    
}
void CPUScheduler::SetLvl(int l)
{
    Level[Level.size()-1].SetCurrentLevel(l);
}
void CPUScheduler::InsertLevelPreempt(Process prem, int lvl)
{
    prem.SetCurrentLevel(lvl);
    Level.insert(Level.begin(), prem);
}
