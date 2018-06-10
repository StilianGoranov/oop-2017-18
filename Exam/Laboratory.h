#include "Study.h"
#include <queue>
#include <iostream>
using std::queue;

class Laboratory 
{
private:
    queue<Study*> studies;
    
    void copy(Laboratory const& other)
    {
        auto shallowCopyQueue = other.studies;
        while(!shallowCopyQueue.empty())
        {
            auto studyPtr = shallowCopyQueue.front();
            studies.push(studyPtr->clone());
            shallowCopyQueue.pop();
        }
    }
    
    void clear()
    {
        while(!studies.empty())
        {
            auto studyPtr = studies.front();
            delete studyPtr;
            studies.pop();
        }
    }
    
public:
    Laboratory() {}
    
    Laboratory(Laboratory const& other)
    {
        copy(other);
    }
    
    Laboratory& operator=(Laboratory const& other)
    {
        if(this != &other)
        {
            clear();
            copy(other);
        }
        return *this;
    }
    
    ~Laboratory() { clear(); }
    
    void addStudy(Study const& newStudy)
    {
        studies.push(newStudy.clone());
    }
    
    void removeStudy() // removes the oldest added study
    {
        if(studies.empty())
        {
            std::cout << "No studies to remove!\n";
            return;
        }
        
        auto studyToRemove = studies.front();
        delete studyToRemove;
        studies.pop();
    }
    
    Study const* getFastestExecutableStudy()
    {
        if(studies.empty())
            return nullptr;
        
        auto shallowCopyQueue = studies;
        auto minTimeStudyPtr = shallowCopyQueue.front();
        auto minTime = minTimeStudyPtr->getTimeForExecution();
        
        shallowCopyQueue.pop();
        
        while(!shallowCopyQueue.empty())
        {
            auto curTimePtr = shallowCopyQueue.front();
            auto curTime = curTimePtr->getTimeForExecution();
            if(minTime > curTime)
            {
                minTime = curTime;
                minTimeStudyPtr = curTimePtr;
            }
            
            shallowCopyQueue.pop();
        }
        
        return minTimeStudyPtr;
    }
    
    double getStudiesPrice() const 
    {
        double result{0};
        auto shallowCopyQueue = studies;
        while(!shallowCopyQueue.empty())
        {
            result += shallowCopyQueue.front()->getPrice();
            shallowCopyQueue.pop();
        }
            
        return result;
    }
    
};
