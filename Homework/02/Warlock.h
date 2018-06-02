#ifndef WARLOCK_H
#define WARLOCK_H

#include "Fighter.h"

class Warlock : virtual public Fighter
{
private:
    double healingPercentage;
    
    void printHealingMessage(double healingAmount, std::ostream& os = std::cout)
    {
        os << this->getName() << " healed for " << healingAmount << " damage.\n";
    }
    
protected:
    void heal(double damageDoneToOther)
    {
        double healingAmount = reduceNumberWithPercentage(damageDoneToOther, healingPercentage);
        setHealth(healingAmount);
        printHealingMessage(healingAmount);
    }
    
public:
    Warlock(std::string _name = "Default", double _health = 0, int _damage = 1, int _armor = 1, int _speed = 1,
        double _healingPercentage = 1)
        : Fighter(_name, _health, _damage, _armor, _speed)
    {
        setHealingPercentage(1);
    }
    
    virtual Fighter* clone() const override
    {
        return new Warlock(*this);
    }
    
    void setHealingPercentage(double _healingPercentage)
    {
        assert(_healingPercentage >= 0 && healingPercentage <= 100);
        healingPercentage = _healingPercentage;
    }
    
    double getHealingPercentage() const { return healingPercentage; }
    
    virtual double attack(Fighter& other) override 
    {
        double damageDoneToOther = Fighter::attack(other);
        heal(damageDoneToOther);
        return damageDoneToOther;
    }
};

#endif // WARLOCK_H
