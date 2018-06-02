#ifndef FIGHTINGTEAM_H
#define FIGHTINGTEAM_H

#include "Warlock.h"
#include "DeathKnight.h"
#include "Warrior.h"
#include <deque>


class FightingTeam
{
private:
    std::string name;
    std::deque<Fighter*> fighters;
    
    void copy(FightingTeam const& other)
    {
        for(auto fighterPtr : other.fighters)
            addFighter(*fighterPtr);
    }
    
    void clear()
    {
        for(auto fighterPtr : fighters)
            delete fighterPtr;
    }
    
public:
    FightingTeam(std::string const& _name = "Default Team Name")
    {
        setName(_name);
    }
    
    FightingTeam(FightingTeam const& other)
    {
        copy(other);
    }
    
    FightingTeam& operator=(FightingTeam const& other)
    {
        if(this != &other)
        {
            clear();
            copy(other);
        }
        
        return *this;
    }
    
    ~FightingTeam()
    {
        clear();
    }
    
    void setName(std::string const& _name)
    {
        name = _name;
    }
    
    std::string const& getName() const { return name; }
    
    Fighter* getFrontFighter() const
    {
        if(!fighters.empty())
            return fighters.front();
        
        return nullptr;
    }
    
    void removeFrontFighter()
    {
        if(!fighters.empty())
        {
            delete fighters.front();
            fighters.pop_front();
        }
    }
    
    void addFighter(Fighter const& fighter)
    {
        fighters.push_back(fighter.clone());
    }
    
    void addFighter(Fighter const* fighter)
    {
        addFighter(*fighter);
    }
    
    int size() const { return fighters.size(); }
    bool empty() const { return fighters.empty(); }
    
};

#endif 
