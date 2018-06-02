#ifndef WARRIOR_H
#define WARRIOR_H

#include "Fighter.h"

class Warrior : virtual public Fighter
{
public:
    Warrior(std::string _name = "Default", double _health = 0, int _damage = 1, int _armor = 1, int _speed = 1)
        : Fighter(_name, _health, _damage, _armor, _speed)
    {}
    
    virtual Fighter* clone() const override
    {
        return new Warrior(*this);
    }
    
    virtual double attack(Fighter& other) override
    {
      int otherArmorBeforeAttack = other.getArmor();
      other.setArmor(0);
      double damageDoneToOther = Fighter::attack(other);
      other.setArmor(otherArmorBeforeAttack);
      return damageDoneToOther;
    }
    
};

#endif // WARRIOR_H
