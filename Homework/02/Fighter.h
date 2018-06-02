#ifndef FIGHTER_H
#define FIGHTER_H

#include <string>
#include <cassert>
#include <iostream>
#include "Cloneable.h"

class Fighter : public Cloneable 
{
    friend class Battle;
    
private:
    
    std::string name;
    double health;
    int damage;
    int armor;
    int speed;
    bool timeToAttack = false;
    
    void printDyingMessage(std::ostream& os = std::cout) const 
    {
        os << name << " died!\n";
    }
    
    void printAttackMessage(Fighter const& adversary, double damage, std::ostream& os = std::cout) const
    {
        os << name << " attacks " << adversary.name << " for " << damage << " damage.\n";
    }
    
    double attack(Fighter* adversary)
    {
        return attack(*adversary);
    }
    
protected:
    
    double reduceNumberWithPercentage(double numToReduce, double percentage)
    {
        return numToReduce -= numToReduce * percentage / 100;
    }
    
public:
    
    Fighter(std::string _name = "Default", double _health = 0, int _damage = 1, int _armor = 1, int _speed = 1)
    {
        setArmor(_armor);
        setDamage(_damage);
        setSpeed(_speed);
        setName(_name);
        setHealth(_health);
    }
    
    virtual Fighter* clone() const override = 0;
    
    void setName(std::string const& _name) { name = _name; }
    
    void setHealth(double _health)
    {
        assert(_health >= 0);
        health = _health;
    }
    
    void setDamage(int _damage)
    {
        assert(_damage > 0);
        damage = _damage;
    }
    
    void setArmor(int _armor)
    {
        assert(_armor >= 0 && _armor <= 99);
        armor = _armor;
    }
    
    void setSpeed(int _speed)
    {
        assert(_speed > 0);
        speed = _speed;
    }
    
    std::string const& getName() const { return name; }
    double getHealth() const { return health; }
    int getDamage() const { return damage; }
    int getSpeed() const { return speed; }
    int getArmor() const { return armor; }
    
    // returns damage done to adversary fighter
    virtual double attack(Fighter& adversary) 
    {
        double healthDamageToOther = reduceNumberWithPercentage(this->damage, adversary.armor);
        printAttackMessage(adversary, healthDamageToOther);
        double adversaryHealthAfterAttack = adversary.health - healthDamageToOther;
        if(adversaryHealthAfterAttack <= 0)
        {
            adversary.printDyingMessage();
            adversary.setHealth(0);
        }
        else 
            adversary.setHealth(adversaryHealthAfterAttack);
        
        return healthDamageToOther;
    }

    bool isDead() const { return health == 0; }
    bool isAlive() const { return !isDead(); }
    void prepareToAttack() { timeToAttack = true; }
    void prepareToDefend() { timeToAttack = false; }
    bool isInAttackMode() const { return timeToAttack; }
};

#endif // FIGHTER_H
