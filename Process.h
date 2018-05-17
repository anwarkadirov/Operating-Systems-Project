#ifndef PROCESS_H
#define PROCESS_H
#include <string>
using namespace std;

class Process{
public:
    Process();
    Process(int, int);
    int GetTimeStamp();
    int GetPID();
    int GetCurrentLevel();
    int GetHardDiskNumber();
    int GetPageNumber();
    int GetTimeQuantum();
    string GetIOFilename();
    void SetCurrentLevel(int);
    void IncreaseTimeQuantum();
    void SetIOFilename(string);
    void SetPageNumber(int);
    void SetTimestamp(int);

    
    
    
private:
    int PID;
    int page;
    int timestamp;
    int hardDrive;
    double timeQuantum;
    int currentLevel;
    string filename;
    
};




#endif
