#pragma once                                                                    
#include <cassert>                                                              
#include <iostream>                                                             
#include "math.h"                                                               
#include <list>                                                                 
                                                                                
using namespace std;                                                            
                                                                                
class StopsSubgroup                                                             
{                                                                               
public:                                                                         
    StopsSubgroup(int _timeOfFirstStop);                                        
    std::list<int>listOfElements;                                               
    int timeOfFirstStop = 0;                                                    
    int numberOfElements = 0;                                                   
    int numberOfSubgroup = 0;                                                   
    std::list<StopsSubgroup*> listOfSubgroups;                                  
    long long int subgroupCost = 0;                                             
                                                                                
    void AddNewStop(int currentStopTime);                                       
    void PrintListOfElements();                                                 
    void ExtendExistingSubgroups(int currentStopTime);                          
    void CreateNewSubgroup(int currentStopTime);                                
    void PrintListOfSubgroups();                                                
    void MakeSummaryOfSubgroups(int subgroupLevelCounter, int variableBits);    
    int CalcualteGroupCost(int subgroupLevelCounter);                           
                                                                                
};                                                                              
                                                                                
class StopsGroup                                                                
{                                                                               
public:                                                                         
    const int MAXIMUM_NUMBER = 1000000007;                                      
    int numberOfFirstStop = 0;                                                  
    int timeOfFirstStop = 0;                                                    
    int elementsNumberUnder20 = 0;                                              
    int elementsNumberUnder70 = 0;                                              
    long long int repetitionsNumber = 0;                                        
    long long int repetitionsNumberWhenCreate = 0;                              
    bool groupActiveFlag = true;                                                
    long long int groupCost = 0;                                                
    int firstElementOver20 = 0;                                                 
    std::list<int> listOfElements;                                              
    std::list<StopsSubgroup*> listOfSubgroups;                                  
    StopsSubgroup* firstGroupOver20 = NULL;                                     
    list<int> summaryOfSubgroups;                                               
    int numberOfSubgroups = 0;                                                  
                                                                                
    void CreateNewGroup(int repetitionsNumber, int stopTime);                   
    void AddNewStop(int currentStopTime);                                       
    void AddNewElements(int currentStopTime);                                   
    void DoubleRepetitionsNumber();                                             
    void ConsiderDeactivation(int currentStopTime);                             
    void CloseThisGroup();                                                      
    void CalculateGroupCost();                                                  
    void SetFirstElementOver20(int currentStopTime);                            
    void PrintListOfElements();                                                 
    void CreateNewSubGroup(int currentStopTime);                                
    void ExtendExistingSubgroups(int currentStopTime);                          
    void PrintListOfSubgroups();                                                
    void MakeSummaryOfSubgroups();                                              
};                                                                              
                                                                                
void StopsGroup::CreateNewGroup(int repetitionsNumber, int stopTime)            
{                                                                               
    this->repetitionsNumber = repetitionsNumber;                                
    this->repetitionsNumberWhenCreate = repetitionsNumber;                      
    this->groupActiveFlag = true;                                               
    this->timeOfFirstStop = stopTime;                                           
}                                                                               
                                                                                
void StopsGroup::AddNewStop(int currentStopTime)                                
{                                                                               
    this->AddNewElements(currentStopTime);                                      
    this->DoubleRepetitionsNumber();                                            
}                                                                               
                                                                                
void StopsGroup::AddNewElements(int currentStopTime)                            
{                                                                               
    int deltaTime = currentStopTime - this->timeOfFirstStop;                    
    assert(deltaTime > 0);                                                      
    this->listOfElements.push_back(currentStopTime);                            
    if (deltaTime < 20)                                                         
    {                                                                           
        elementsNumberUnder20++;                                                
    }                                                                           
    else if (deltaTime >= 20)                                                   
    {                                                                           
        ExtendExistingSubgroups(currentStopTime);                               
        this->CreateNewSubGroup(currentStopTime);                               
        this->numberOfSubgroups++;                                              
    }                                                                           
}                                                                               
                                                                                
void StopsGroup::DoubleRepetitionsNumber()                                      
{                                                                               
    this->repetitionsNumber *= 2;                                               
    this->repetitionsNumber %= MAXIMUM_NUMBER;                                  
}                                                                               
                                                                                
void StopsGroup::ConsiderDeactivation(int currentStopTime)                      
{                                                                               

    if (currentStopTime - this->timeOfFirstStop > 69)                           
    {                                                                           
        this->CloseThisGroup();                                                 
    }                                                                           
}                                                                               
                                                                                
void StopsGroup::CloseThisGroup()                                               
{                                                                               
    this->groupActiveFlag = false;                                              
    this->MakeSummaryOfSubgroups();                                             
    this->CalculateGroupCost();                                                 
}                                                                               
                                                                                
void StopsGroup::CalculateGroupCost()                                           
{                                                                               
    for (list<StopsSubgroup*>::iterator iter = listOfSubgroups.begin(); iter != listOfSubgroups.end(); ++iter)                                                  
    {                                                                           
        this->groupCost += this->repetitionsNumberWhenCreate * (*iter)->subgroupCost;                                                                           
    }                                                                           
    this->groupCost += this->repetitionsNumberWhenCreate * pow(2, this->elementsNumberUnder20) * 2;                                                             
}                                                                               
                                                                                
void StopsGroup::SetFirstElementOver20(int currentStopTime)                     
{                                                                               
    if (firstElementOver20 == 0)                                                
    {                                                                           
        this->firstElementOver20 = currentStopTime;                             
    }                                                                           
}                                                                               
                                                                                
void StopsGroup::PrintListOfElements()                                          
{                                                                               
    for (std::list<int>::iterator iter = this->listOfElements.begin(); iter != this->listOfElements.end(); ++iter)                                              
    {                                                                           
        std::cout << *iter << "\t";                                             
    }                                                                           
    std::cout << "\n";                                                          
}                                                                               
                                                                                
void StopsGroup::CreateNewSubGroup(int currentStopTime)                         
{                                                                               
    this->listOfSubgroups.push_back(new StopsSubgroup(currentStopTime));        
}                                                                               
                                                                                
void StopsGroup::ExtendExistingSubgroups(int currentStopTime)                   
{                                                                               
    for (std::list<StopsSubgroup*>::iterator iter = this->listOfSubgroups.begin(); iter != this->listOfSubgroups.end(); ++iter)                                 
    {                                                                           
        (*iter)->AddNewStop(currentStopTime);                                   
    }                                                                           
}                                                                               
                                                                                
void StopsGroup::PrintListOfSubgroups()                                         
{                                                                               
    if (this->listOfSubgroups.size() > 0)                                       
    {                                                                           
        for (std::list<StopsSubgroup*>::iterator iter = this->listOfSubgroups.begin(); iter != this->listOfSubgroups.end(); ++iter)                             
        {                                                                       
            std::cout << "podgrupa - liczba podgrup: " << this->listOfSubgroups.size() << "\n";                                                                 
            (*iter)->PrintListOfElements();                                     
        }                                                                       
    }                                                                           
}                                                                               
                                                                                
void StopsGroup::MakeSummaryOfSubgroups()                                       
{                                                                               
    int subgroupLevelCounter = 1;                                               
    int groupVariants = pow(2, elementsNumberUnder20);                          
    int localGroupCost = 0;                                                     
    int numberOfSubgroupVariants = 0;                                           
    if (numberOfSubgroups > 0)                                                  
    {                                                                           
        subgroupLevelCounter++;                                                 
        for (list<StopsSubgroup*>::iterator iter = listOfSubgroups.begin(); iter != listOfSubgroups.end(); ++iter)                                              
        {                                                                       
            summaryOfSubgroups.push_back((*iter)->numberOfElements);            
            numberOfSubgroupVariants = groupVariants * pow(2, (*iter)->numberOfElements);                                                                       
            if ((*iter)->numberOfSubgroup > 0)                                  
            {                                                                   
                subgroupLevelCounter++;                                         
                (*iter)->MakeSummaryOfSubgroups(subgroupLevelCounter, numberOfSubgroupVariants);                                                                
                subgroupLevelCounter--;                                         
                localGroupCost = (*iter)->CalcualteGroupCost(subgroupLevelCounter);                                                                             
                (*iter)->subgroupCost += localGroupCost * numberOfSubgroupVariants;                                                                             
                                                                                
            }                                                                   
            else                                                                
            {                                                                   
                localGroupCost = (*iter)->CalcualteGroupCost(subgroupLevelCounter);                                                                             
                (*iter)->subgroupCost += numberOfSubgroupVariants * localGroupCost;                                                                             
            }                                                                   
        }                                                                       
        subgroupLevelCounter--;                                                 
    }                                                                           
    summaryOfSubgroups.push_back(-1);                                           
}                                                                               
                                                                                
                                                                                
/// SubGroup                                                                    
                                                                                
StopsSubgroup::StopsSubgroup(int _timeOfFirstStop)                              
{                                                                               
    this->timeOfFirstStop = _timeOfFirstStop;                                   
}                                                                               
                                                                                
void StopsSubgroup::AddNewStop(int currentStopTime)                             
{                                                                               
    int deltaTime = currentStopTime - this->timeOfFirstStop;                    
    assert(deltaTime > 0);                                                      
    if (deltaTime < 20)                                                         
    {                                                                           
        this->listOfElements.push_back(currentStopTime);                        
        this->numberOfElements++;                                               
    }                                                                           
    else if (deltaTime >= 20)                                                   
    {                                                                           
        ExtendExistingSubgroups(currentStopTime);                               
        this->CreateNewSubgroup(currentStopTime);                               
        numberOfSubgroup++;                                                     
    }                                                                           
}                                                                               
                                                                                
void StopsSubgroup::PrintListOfElements()                                       
{                                                                               
    std::cout << this->timeOfFirstStop << "\t";                                 
    for (std::list<int>::iterator iter = this->listOfElements.begin(); iter != this->listOfElements.end(); ++iter)                                              
    {                                                                           
        std::cout << *iter << " ";                                              
    }                                                                           
    std::cout << "\n";                                                          
    this->PrintListOfSubgroups();                                               
}                                                                               
                                                                                
void StopsSubgroup::ExtendExistingSubgroups(int currentStopTime)                
{                                                                               
    for (std::list<StopsSubgroup*>::iterator iter = this->listOfSubgroups.begin(); iter != this->listOfSubgroups.end(); ++iter)                                 
    {                                                                           
        (*iter)->AddNewStop(currentStopTime);                                   
    }                                                                           
}                                                                               
                                                                                
void StopsSubgroup::CreateNewSubgroup(int currentStopTime)                      
{                                                                               
    this->listOfSubgroups.push_back(new StopsSubgroup(currentStopTime));        
}                                                                               
                                                                                
void StopsSubgroup::PrintListOfSubgroups()                                      
{                                                                               
    if (this->listOfSubgroups.size() > 0)                                       
    {                                                                           
        std::cout << "kolejne podgrupy - liczba podgrup - " << this->listOfSubgroups.size() << "\n";                                                            
        for (std::list<StopsSubgroup*>::iterator iter = this->listOfSubgroups.begin(); iter != this->listOfSubgroups.end(); ++iter)                             
        {                                                                       
            (*iter)->PrintListOfElements();                                     
        }                                                                       
    }                                                                           
}                                                                               
                                                                                
void StopsSubgroup::MakeSummaryOfSubgroups(int subgroupLevelCounter, int variableBits)                                                                          
{                                                                               
    int groupCost = 0;                                                          
    for (std::list<StopsSubgroup*>::iterator iter = this->listOfSubgroups.begin(); iter != this->listOfSubgroups.end(); ++iter)                                 
    {                                                                           
        if ((*iter)->numberOfSubgroup > 0)                                      
        {                                                                       
            subgroupLevelCounter++;                                             
            (*iter)->MakeSummaryOfSubgroups(subgroupLevelCounter, variableBits * pow(2, (*iter)->numberOfElements));                                            
            subgroupLevelCounter--;                                             
            groupCost = this->CalcualteGroupCost(subgroupLevelCounter);         
            (*iter)->subgroupCost += variableBits * pow(2, (*iter)->numberOfElements) * groupCost;                                                              
            this->subgroupCost += (*iter)->subgroupCost;                        
        }                                                                       
        else                                                                    
        {                                                                       
            groupCost = this->CalcualteGroupCost(subgroupLevelCounter);         
            this->subgroupCost += variableBits * pow(2, (*iter)->numberOfElements) * groupCost;                                                                 
        }                                                                       
    }                                                                           
}                                                                               
                                                                                
int StopsSubgroup::CalcualteGroupCost(int subgroupLevelCounter)                 
{                                                                               
    if (subgroupLevelCounter > 3)                                               
    {                                                                           
        return 6; //cost of 70 min ticket                                       
    }                                                                           
    else                                                                        
    {                                                                           
        return 2 * subgroupLevelCounter; //one ticekt for each group;           
    }                                                                           
}                                                                               
                                                                                
int main()                                                                      
{                                                                               
    const int MAXIMUM_NUMBER = 1000000007;                                      
    int numberOfStops;                                                          
    std::cin >> numberOfStops;                                                  
    int* stopsTime = new int[numberOfStops];                                    
    for (int i = 0; i < numberOfStops; i++)                                     
    {                                                                           
        std::cin >> stopsTime[i];                                               
        //stopsTime[i] = i * 5 + 1;                                             
    }                                                                           
    long long int onesNumber = 1;                                               
    long long int activeGroup = 0;                                              
    long long int wallet = 0;                                                   
    StopsGroup* stopsGroup = new StopsGroup[numberOfStops];                     
                                                                                
    int z = 0;                                                                  
    while (z < numberOfStops)                                                   
    {                                                                           
        for (int i = 0; i < z; i++)                                             
        {                                                                       
            if (stopsGroup[i].groupActiveFlag)                                  
            {                                                                   
                stopsGroup[i].ConsiderDeactivation(stopsTime[z]);               
                wallet += stopsGroup[i].groupCost; // if group is active cost is 0                                                                              
                wallet %= MAXIMUM_NUMBER;                                       
            }                                                                   
        }                                                                       
        activeGroup = 0;                                                        
        for (int i = 0; i < z; i++)                                             
        {                                                                       
            if (stopsGroup[i].groupActiveFlag)                                  
            {                                                                   
                activeGroup += stopsGroup[i].repetitionsNumber;                 
                if (activeGroup > MAXIMUM_NUMBER)                               
                {                                                               
                    activeGroup %= MAXIMUM_NUMBER;                              
                }                                                               
            }                                                                   
        }                                                                       
        if (onesNumber - activeGroup < 0)                                       
        {                                                                       
            onesNumber += MAXIMUM_NUMBER;                                       
        }                                                                       
        stopsGroup[z].CreateNewGroup(onesNumber - activeGroup, stopsTime[z]);   
        for (int i = 0; i < z; i++)                                             
        {                                                                       
            if (stopsGroup[i].groupActiveFlag)                                  
            {                                                                   
                stopsGroup[i].AddNewStop(stopsTime[z]);                         
            }                                                                   
        }                                                                       
        z++;                                                                    
        onesNumber *= 2;                                                        
        wallet *= 2;                                                            
        onesNumber %= MAXIMUM_NUMBER;                                           
        wallet %= MAXIMUM_NUMBER;                                               
    }                                                                           
    for (int i = 0; i < z; i++)                                                 
    {                                                                           
        if (stopsGroup[i].groupActiveFlag)                                      
        {                                                                       
            stopsGroup[i].CloseThisGroup();                                     
            wallet += stopsGroup[i].groupCost;                                  
        }                                                                       
    }                                                                           
    /*                                                                          
    for (int i = 0; i < z; i++)                                                 
    {                                                                           
        std::cout << "cala grupa: \n";                                          
        std::cout << stopsGroup[i].timeOfFirstStop << "\t";                     
        stopsGroup[i].PrintListOfElements();                                    
        stopsGroup[i].PrintListOfSubgroups();                                   
    }                                                                           
    */                                                                          
    std::cout << wallet << "\n";                                                
    delete[] stopsGroup;                                                        
    delete[] stopsTime;                                                         
}         