#ifndef DEATHKNIGHT_H
#define DEATHKNIGHT_H

#include "Warlock.h"
#include "Warrior.h"

class DeathKnight : public Warlock, public Warrior
{
public:
    
    DeathKnight(std::string _name = "Default", double _health = 0, int _damage = 1, int _armor = 1, int _speed = 1,
        double _healingPercentage = 1)
        : Fighter(_name, _health, _damage, _armor, _speed), 
        Warlock(_name, _health, _damage, _armor, _speed, _healingPercentage)
    {}
    
    virtual double attack(Fighter& other) override
    {
        double damageDoneToOther = Warrior::attack(other);
        heal(damageDoneToOther);
    }
    
    virtual Fighter* clone() const override 
    {
        return new DeathKnight(*this);
    }
    
};

#endif // DEATHKNIGHT_H
