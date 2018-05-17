//Anwar Kadirov
//Operating Systems
//Section 1
#include <iostream>
#include <sstream>
#include "Process.h"
#include "CPUScheduler.hpp"
using namespace std;

void MoveHighestProcess(CPUScheduler &, CPUScheduler &, CPUScheduler &, vector<Process> &);

int main ()
{
    vector<Process> CPU;
    vector<Process> IOQueueNumber;
    vector <vector<Process> > HardDisks;
    vector<double> HardDisksName;
    vector <Process> PageTable;
    int processssID = 1, ProcessIDtemp, Timestamptemp, numberDD2 = 0, numberM = 0, timeStamp = 1;
    double hardDiskNumber = 0;
    auto RAMsize =0, pageSize=0, hardD = 0;
    Process nullInitialize;
    CPU.push_back(nullInitialize);
    IOQueueNumber.push_back(nullInitialize);
    CPUScheduler levelZero, levelOne,levelTwo;
    cout << "How much RAM memory is there on the simulated computer?" << endl;
    cin >> RAMsize;
    cout << "What is the size of a page/frame?" << endl;
    cin >> pageSize;
    cout << "How many hard disks does this simulated computer have?" << endl;
    cin >> hardD;
    //Initializes amount of Hard Disks based on user input
    for (int q =0;q<hardD;q++)
    {
        HardDisks.push_back(IOQueueNumber);
        HardDisksName.push_back(hardDiskNumber);
        hardDiskNumber++;
    }
    //Takes the memory size and page size and creates the number of frames
    int pages = RAMsize/pageSize;
    for(int e=0;e<pages;e++)
    {
        PageTable.push_back(nullInitialize);
    }
    cout << "Begin inputting commands: " << endl;
    string yamom;
    //Program will read input as long as user would like
    while (getline(cin,yamom) && yamom!= "exit")
    {
        //d number file_name command
        //The process that currently uses the CPU requests the hard disk #number. It wants to read or write file file_name.
        if(yamom[0] == 'd')
        {
            int dNumber1 = 0;
            string filenameD;
            int k;
            for(k = 2; k < yamom.size(); k++)
            {
                if(yamom[k]!= ' ')
                {
                    string dNumber;
                    dNumber += yamom[k];
                    stringstream String2Num(dNumber);
                    String2Num >> dNumber1;

                }
                if(yamom[k]== ' ')
                {
                    break;
                }
            }
            int l;
            for (l = k+1; l < yamom.size();l++)
            {
                filenameD+= yamom[l];
            }
            if(HardDisks[dNumber1][0].GetPID() == nullInitialize.GetPID())
            {
                CPU[0].SetIOFilename(filenameD);
                HardDisks[dNumber1][0] = CPU[0];
                
                CPU[0] = nullInitialize;
                MoveHighestProcess(levelZero, levelOne, levelTwo, CPU);
            }
            else if(HardDisks[dNumber1][0].GetPID() != 0)
            {
                CPU[0].SetIOFilename(filenameD);
                HardDisks[dNumber1].push_back(CPU[0]);
                dNumber1 = 0;
                CPU[0] = nullInitialize;
                MoveHighestProcess(levelZero, levelOne, levelTwo, CPU);
                

            }
           
            
        }
        //D number command
        //The hard disk #number has finished the work for one process.
        if(yamom[0] == 'D')
        {
            for(int y = 2; y<yamom.size();y++)
            {
                string numberD;
                numberD+= yamom[y];
                stringstream String2Num2(numberD);
                String2Num2 >> numberDD2;
                
            }
            
                if(CPU[0].GetCurrentLevel() == 0)
                {
                    levelZero.InsertLevelNew(CPU[0],0);
                    CPU[0] = nullInitialize;
                }
                else if(CPU[0].GetCurrentLevel() == 1)
                {
                    levelOne.InsertLevelNew(CPU[0], 1);
                    CPU[0] = nullInitialize;
                
                }
                else if(CPU[0].GetCurrentLevel() == 2)
                {
                    levelTwo.InsertLevelNew(CPU[0], 2);
                    CPU[0] = nullInitialize;
                }
           
            if(HardDisks[numberDD2][0].GetCurrentLevel() == 0)
            {
                levelZero.InsertLevelNew(HardDisks[numberDD2][0], 0);
            }
            else if(HardDisks[numberDD2][0].GetCurrentLevel() == 1)
            {
                levelOne.InsertLevelNew(HardDisks[numberDD2][0], 1);
            }
            else if(HardDisks[numberDD2][0].GetCurrentLevel() == 2)
            {
                levelTwo.InsertLevelNew(HardDisks[numberDD2][0], 2);
            }
    
            HardDisks[numberDD2].erase(HardDisks[numberDD2].begin());
            HardDisks[numberDD2].push_back(nullInitialize);
            
            MoveHighestProcess(levelZero, levelOne, levelTwo, CPU);
        }
        // m address command
        // The process that is currently using the CPU requests a memory operation for the logical address.
        if(yamom[0] == 'm')
        {
            string number4;
            for(int p = 2;p<yamom.size();p++)
            {
                
                number4+=yamom[p];
                stringstream String2Num3(number4);
                String2Num3 >> numberM;
            }
    
            int logicalPage = numberM/pageSize;
            int LeastRecent = 1000;
            Process temp = CPU[0];
            temp.SetTimestamp(timeStamp);
            temp.SetPageNumber(logicalPage);
            for(int t=0;t<PageTable.size();t++)
            {
                if(LeastRecent > PageTable[t].GetTimeStamp())
                {
                    LeastRecent = PageTable[t].GetTimeStamp();
                }
                
            }
            for(int fo = 0; fo<PageTable.size();fo++)
            {
                if(PageTable[fo].GetTimeStamp() == 0)
                {
                   
                    PageTable[fo] = temp;
                    break;
                }
                else if(PageTable[fo].GetPageNumber() == temp.GetPageNumber() && PageTable[fo].GetPID() == temp.GetPID())
                {
                    PageTable[fo].SetTimestamp(timeStamp);
                    break;
                }
                else if(PageTable[fo].GetTimeStamp() == LeastRecent)
                {
                    
                   
                    PageTable[fo] = temp;
                    break;
                    
                }
                
            }
            timeStamp++;
                
        }
        
        
        //A command
        //A new process has been created.
        if(yamom == "A")
        {
            Timestamptemp = timeStamp;
            ProcessIDtemp = processssID;
            Process p(ProcessIDtemp, Timestamptemp);
            processssID++;
            //timeStamp++;
            if(CPU[0].GetPID() == 0)
            {
                    CPU[0] = p;
            }
            else
            {
                p.SetCurrentLevel(0);
                levelZero.InsertLevelNew(p, 0);
            
                if(CPU[0].GetCurrentLevel() == 1 && !levelZero.isEmpty())
                {

                    levelOne.InsertLevelPreempt(CPU[0], 1);
                    levelZero.MoveToCPU(CPU);
                }
                else if(CPU[0].GetCurrentLevel() == 2 && !levelZero.isEmpty())
                {
                
                    levelTwo.InsertLevelPreempt(CPU[0], 2);
                    levelZero.MoveToCPU(CPU);
                }
        
                
            }
            int logicalPage = numberM/pageSize;
            int LeastRecent = 1000;
            p.SetTimestamp(timeStamp);
            
            for(int t=0;t<PageTable.size();t++)
            {
                if(LeastRecent > PageTable[t].GetTimeStamp())
                {
                    LeastRecent = PageTable[t].GetTimeStamp();
                }
                
            }
            for(int fo = 0; fo<PageTable.size();fo++)
            {
                if(PageTable[fo].GetTimeStamp() == 0)
                {
                    p.SetPageNumber(logicalPage);
                    PageTable[fo] = p;
                    break;
                }
                else if(PageTable[fo].GetTimeStamp() == LeastRecent)
                {
                    
                    p.SetPageNumber(logicalPage);
                    PageTable[fo] = p;
                    break;
                    
                }
                
            }
            
            timeStamp++;
            
            
        }
        //Q command
        //The currently running process has spent a time quantum using the CPU.
        if(yamom == "Q")
        {
            
            if(CPU[0].GetCurrentLevel() == 0)
            {
                CPU[0].IncreaseTimeQuantum();
                levelOne.InsertLevelNew(CPU[0], 1);
                CPU[0] = nullInitialize;
                MoveHighestProcess(levelZero, levelOne, levelTwo, CPU);
                
                
            
            }
            else if(CPU[0].GetCurrentLevel() == 1)
            {
                if(CPU[0].GetTimeQuantum() != 3)
                {
                CPU[0].IncreaseTimeQuantum();
                }
                if(CPU[0].GetTimeQuantum() == 3)
                {
                    levelTwo.InsertLevelNew(CPU[0], 2);
                    CPU[0] = nullInitialize;
                    MoveHighestProcess(levelZero, levelOne, levelTwo, CPU);
                }
            }
            else if(CPU[0].GetCurrentLevel() == 2)
            {
                MoveHighestProcess(levelZero, levelOne, levelTwo, CPU);
            }
        
            
        }
        //t command
        //The process that is currently using the CPU terminates.
        if(yamom == "t")
        {
            
            for (int yo = 0; yo<PageTable.size();yo++)
            {
                if(PageTable[yo].GetPID() == CPU[0].GetPID())
                {
                    PageTable[yo] = nullInitialize;
                }
            }
            CPU.erase(CPU.begin());
            CPU.push_back(nullInitialize);
            CPU[0] = nullInitialize;
            MoveHighestProcess(levelZero, levelOne, levelTwo, CPU);

        }
        //S i command
        //Shows what processes are currently using the hard disks and what processes are waiting to use them.
        if(yamom == "S i")
        {
            for(int a=0;a<HardDisks.size();a++)
            {
                cout << "Process currently using hard disk " << HardDisksName[a] << ": ";
                if(HardDisks[a][0].GetPID() == 0)
                {
                    cout << "EMPTY" << endl;
                }
                else{
                    cout << "------> PID: " << HardDisks[a][0].GetPID() << " filename: " << HardDisks[a][0].GetIOFilename() << endl;
                }
                cout << endl;
                cout << "Processes in IO queue currently waiting to use hard disk " << HardDisksName[a] << ": ";
                if(HardDisks[a][1].GetPID() == 0)
                {
                    cout << "EMPTY" << endl;
                }
                else{
                    int positio = 1;
                    for(int u=1; u<HardDisks[a].size();u++)
                    {
                        cout << endl << positio <<  ") PID: " << HardDisks[a][u].GetPID() << " filename: " << HardDisks[a][u].GetIOFilename() << endl;
                    }
                    
                }
                cout << "-----------------------------------------------------------------------------------------" << endl << endl;;
            }
           
        }
        //S r command
        //Shows what process is currently using the CPU and what processes are waiting in the ready-queue.
        if(yamom == "S r")
        {
            
            if(CPU[0].GetPID() == 0)
            {
                cout << "No processes in ready queue" << endl;
            }
            else
            {
                cout << "Process currently using the CPU------> PID: " << CPU[0].GetPID() << " from Level " << CPU[0].GetCurrentLevel() << " queue" << endl << endl;
               
                cout << "Processes in Level Zero Queue (RR):" << endl;
                levelZero.ShowProcesses();
                cout << "-----------------------------------------------------------------------------------------" << endl << endl;
                cout << "Processes in Level One Queue (RR):" << endl;
                levelOne.ShowProcesses();
                cout << "-----------------------------------------------------------------------------------------" << endl << endl;
                cout << "Processes in Level Two Queue (FCFS):" << endl;
                levelTwo.ShowProcesses();
                cout << "-----------------------------------------------------------------------------------------" << endl << endl;
                cout << endl;
            }
            
        }
        //S m command
        //Shows the state of memory.
        if(yamom == "S m")
        {
            cout << "Showing current state of memory: " << endl;
            for(int z=0;z<PageTable.size();z++)
            {
                if(PageTable[z].GetTimeStamp() != 0)
                {
                cout << "Frame: " << z << endl;
                cout << "PID: " << PageTable[z].GetPID() << endl;
                cout << "Page Number: " << PageTable[z].GetPageNumber() << endl;
                cout << "Timestamp: " << PageTable[z].GetTimeStamp() << endl;
                cout << "-----------------------------------------------------------------------------------------" << endl << endl;
                }
                else{
                    cout << "Frame: " << z << endl;
                    cout << "EMPTY" << endl;
                    cout << "-----------------------------------------------------------------------------------------" << endl << endl;
                }
            }
        }
        if(yamom[0] == 'y')
        {
            cout << "This is the current level: " << CPU[0].GetCurrentLevel() << endl;
            cout << "This is the current time quantum: " << CPU[0].GetTimeQuantum() << endl;
        }
        
    }
    return 0;
}

void MoveHighestProcess(CPUScheduler &lvl0 , CPUScheduler &lvl1, CPUScheduler &lvl2, vector<Process> &cpizzle)
{
    if(!lvl0.isEmpty())
    {
        lvl0.MoveToCPU(cpizzle);
        
    }
    else if(lvl0.isEmpty() && !lvl1.isEmpty())
    {
        lvl1.MoveToCPU(cpizzle);
        
    }
    else if(lvl0.isEmpty() && lvl1.isEmpty() && !lvl2.isEmpty())
    {
        lvl2.MoveToCPU(cpizzle);
        
    }
    else if(lvl0.isEmpty() && lvl1.isEmpty() && lvl2.isEmpty())
    {
        ;
        
    }
}
