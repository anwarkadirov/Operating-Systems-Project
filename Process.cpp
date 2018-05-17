#include <iostream>
#include "Process.h"
using namespace std;

Process::Process()
{
    PID = 0;
    timestamp = 0;
    currentLevel = 0;
    filename = ' ';
    page = 0;
    timeQuantum = 0;
}
Process::Process(int P, int T)
{
    PID = P;
    timestamp = T;
    currentLevel = 0;
    filename = ' ';
    page = 0;
    timeQuantum = 0;
}

int Process::GetTimeStamp()
{
    return timestamp;
}
int Process::GetPID()
{
    return PID;
}
int Process::GetCurrentLevel()
{
    return currentLevel;
}
int Process::GetHardDiskNumber()
{
    return hardDrive;
}
int Process::GetPageNumber()
{
    return page;
}
int Process::GetTimeQuantum()
{
    return timeQuantum;
}
string Process::GetIOFilename()
{
    return filename;
}
void Process::SetCurrentLevel(int plvl)
{
    currentLevel = plvl;
}
void Process::SetIOFilename(string fName)
{
    filename = fName;
}
void Process::SetPageNumber(int pager)
{
    page = pager;
}
void Process::SetTimestamp(int stamp)
{
    timestamp = stamp;
}
void Process::IncreaseTimeQuantum()
{
    timeQuantum = timeQuantum +1;
}
