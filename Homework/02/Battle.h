#ifndef BATTLE_H
#define BATTLE_H

#include "FightingTeam.h"

class Battle 
{
private:

    FightingTeam *ft1, *ft2;

private:
    
    class MessageUtility 
    {    
    public:
        
        static void printStartingBattleBetweenTeamsMessage(FightingTeam const* ft1, FightingTeam const* ft2, std::ostream& os = std::cout)
        {
            os << "Battle between " << ft1->getName() << " and " << ft2->getName() << " begins!" << std::endl;
        }
        
        static void printDrawBetweenTeamsMessage(FightingTeam const* ft1, FightingTeam const* ft2, std::ostream& os = std::cout)
        {
            os << "Battle between " << ft1->getName() << " and " << ft2->getName() << " ended in a draw!" << std::endl;
        }
        
        static void printWinningTeamMessage(FightingTeam const* winner, FightingTeam const* loser, std::ostream& os = std::cout) 
        {
            os << winner->getName() << " won the battle against " << loser->getName() << "!\n";
        }
        
        static void printWinningFighterMessage(Fighter const* winner, Fighter const* loser, std::ostream& os = std::cout) 
        {
            os << winner->getName() << " won a fight against " << loser->getName() << "!\n";
        }
        
        static void printCurrentFightAnnouncement(Fighter const* f1, Fighter const* f2, std::ostream& os = std::cout)  
        {
            os << "Current battle: " << f1->getName() << " vs " << f2->getName() << std::endl;
        }
        
        static void printBothFightersDeadDrawMessage(Fighter const* f1, Fighter const* f2, std::ostream& os = std::cout) 
        {
            os << f1->getName() << " and " << f2->getName() << " are both dead! " << std::endl;
        }
        
        static void printEqualSpeedRandomChoiceForFirstAttackerMessage(Fighter const* f1, Fighter const* f2, std::ostream& os = std::cout) 
        {
            os << f1->getName() << " and " << f2->getName() << " have equal speed! Who will attack first will be a random choice.\n";
        }
    };
    
    Fighter* fightUntilSomeoneDies(Fighter* attacksFirst, Fighter* attacksSecond) 
    {
        while(attacksFirst->isAlive() && attacksSecond->isAlive())
        {
            attacksFirst->attack(attacksSecond);
            if(attacksSecond->isAlive()) 
                attacksSecond->attack(attacksFirst);
        }
        
        if(attacksFirst->isDead())
        {
            MessageUtility::printWinningFighterMessage(attacksSecond, attacksFirst);
            return attacksSecond;
        }
        else 
        {
            MessageUtility::printWinningFighterMessage(attacksFirst, attacksSecond);
            return attacksFirst;
        }
    }
    
    // helping methods for fighting 
    
    // returns the winner, nullptr if nobody wins the fight
    Fighter* fight(Fighter* f1, Fighter* f2)
    {
        if(f1->isDead() && f2->isDead())
        {
            MessageUtility::printBothFightersDeadDrawMessage(f1, f2);
            return nullptr;
        }
        else if(f1->isDead())
            return f2;
        else if(f2->isDead())
            return f1;
        else // f1 and f2 are alive
        {
            if(!f1->isInAttackMode() && !f2->isInAttackMode())
            // speed decides who should attack first
            {
                Fighter* faster = whoHasHigherSpeed(f1, f2);
                if(faster == nullptr) // equal speed, should use rand()
                {
                    MessageUtility::printEqualSpeedRandomChoiceForFirstAttackerMessage(f1, f2);
                    bool f1_attacks = fiftyPercentChance();
                    if(f1_attacks) 
                        return fightUntilSomeoneDies(f1, f2);
                    else 
                        return fightUntilSomeoneDies(f2, f1);
                }
                else if(faster == f1)
                {
                    Fighter* winner = fightUntilSomeoneDies(f1, f2);
                    return winner;
                }
                else // f2 has more speed
                {
                    Fighter* winner = fightUntilSomeoneDies(f2, f1);
                    return winner;
                }
            }
            else if(f1->isInAttackMode())
            // f1 attacks first
            {
                Fighter* winner = fightUntilSomeoneDies(f1, f2);
                return winner;
            }
            else
            // f2 attacks first
            {
                Fighter* winner = fightUntilSomeoneDies(f2, f1);
                return winner;
            }
        }
    }
    
    Fighter* whoHasHigherSpeed(Fighter* f1, Fighter* f2) const 
    {
        if(f1->getSpeed() > f2->getSpeed())
            return f1;
        else if (f2->getSpeed() > f1->getSpeed())
            return f2;
        else 
            return nullptr;
    }
    
    bool fiftyPercentChance() const 
    {
        srand(static_cast<unsigned int>(time(0)));
        bool chance = rand() % 2 == 0;
        return chance;
    }
    
public:
    
    Battle(FightingTeam* _ft1, FightingTeam* _ft2)
    {
        setTeams(_ft1, _ft2);
    }
    
    void setTeams(FightingTeam* _ft1, FightingTeam* _ft2)
    {
        assert(_ft1 && _ft2 && _ft1 != _ft2);
        ft1 = _ft1;
        ft2 = _ft2;
    }
    
    auto getTeams() const 
    {
        return std::make_pair(ft1, ft2);
    }
    
    void startBattle() 
    {
        MessageUtility::printStartingBattleBetweenTeamsMessage(ft1, ft2);
        
        while(!ft1->empty() && !ft2->empty())
        {
            Fighter* fighter1 = ft1->getFrontFighter();
            Fighter* fighter2 = ft2->getFrontFighter();
            MessageUtility::printCurrentFightAnnouncement(fighter1, fighter2);
            Fighter* winner = fight(fighter1, fighter2);
            if(winner == fighter1)
            {
                ft2->removeFrontFighter();
                fighter1->prepareToAttack();
            }
            else if(winner == fighter2)
            {
                ft1->removeFrontFighter();
                fighter2->prepareToAttack();
            }
            else // draw between fighters, winner == nullptr
            {
                ft1->removeFrontFighter();
                ft2->removeFrontFighter();
            }
        }
        
        if(ft1->empty() && ft2->empty())
            MessageUtility::printDrawBetweenTeamsMessage(ft1, ft2);
        else if(ft1->empty())
            MessageUtility::printWinningTeamMessage(ft2, ft1);
        else
            MessageUtility::printWinningTeamMessage(ft1, ft2);
    }
};

#endif 
