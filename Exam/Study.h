#ifndef _STUDY_H
#define _STUDY_H

#include <string>
#include <cassert>
#include <vector>
#include "Cloneable.h"
using std::vector;
using std::string;

class Study : public Cloneable
{
private:
    string name = "DefaultStudyName";
    double minBound = 0;
    double maxBound = 10;
    
public:
    Study(string _name = "DefaultStudyName", double _minBound = 0, double _maxBound = 10)
    {
        setMaxBound(_maxBound);
        setMinBound(_minBound);
        setName(_name);
    }
    
    void setMinBound(double _minBound) { minBound = _minBound; }
    void setMaxBound(double _maxBound) { maxBound = _maxBound; }
    void setName(string _name) { name = _name; }
    
    string getName() const { return name; }
    auto getMinBound() const { return minBound;}
    auto getMaxBound() const { return maxBound; }
    
    virtual Study* clone() const override = 0;
    virtual double getPrice() const = 0;
    virtual double getTimeForExecution() const = 0;
};

class SingleStudy : public Study
{
private:
    double price;
    double timeForExecution;
    
public:
    SingleStudy(string _name = "DefaultName", double _price = 0, double _timeForExecution = 0, double _minBound = 0, double _maxBound = 10)
        : Study(_name, _minBound, _maxBound)
    {
        setPrice(_price);
        setTimeForExecution(_timeForExecution);
    }
    
    void setPrice(double _price)
    {
        assert(_price >= 0);
        price = _price;
    }
    
    void setTimeForExecution(double _timeForExecution)
    {
        assert(_timeForExecution > 0);
        timeForExecution = _timeForExecution;
    }
    
    virtual double getPrice() const override { return price; }
    virtual double getTimeForExecution() const override { return timeForExecution; }
    virtual SingleStudy* clone() const override { return new SingleStudy(*this); }
};

class PackageStudy : public Study
{
private:
    vector<Study*> package;
    
    void copy(PackageStudy const& other)
    {
        Study::operator=(other);
        for(auto studyPtr : other.package)
            package.push_back(studyPtr->clone());
    }
    
    void clear()
    {
        for(auto studyPtr : package)
            delete studyPtr;
    }
    
public:
    PackageStudy(string _name = "DefaultName", double _minBound = 0, double _maxBound = 10)
        : Study(_name, _minBound, _maxBound)
    {}
    
    PackageStudy(PackageStudy const& other)
    {
        copy(other);
    }
    
    PackageStudy& operator=(PackageStudy const& other)
    {
        if(this != &other)
        {
            clear();
            copy(other);
        }
        
        return *this;
    }
    
    ~PackageStudy() { clear(); }
    
    void addStudy(Study const& newStudy)
    {
        package.push_back(newStudy.clone());
    }
    
    virtual double getTimeForExecution() const override
    {
        if(package.empty())
            return 0;
            
        double maxTime = package[0]->getTimeForExecution();
        for(auto studyPtr : package)
        {
            auto curTime = studyPtr->getTimeForExecution();
            if(maxTime < curTime)
                maxTime = curTime;
        }
        
        return maxTime;
    }
    
    virtual double getPrice() const override 
    {
        double result{0};
        for (auto studyPtr : package)
            result += studyPtr->getPrice();
        
        return result -= 0.1 * result;
    }
    
    virtual PackageStudy* clone() const override { return new PackageStudy(*this); }
};

#endif 
