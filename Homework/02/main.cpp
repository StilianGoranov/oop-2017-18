#include <iostream>
#include "Battle.h"

FightingTeam createTestFightingTeam1()
{
    FightingTeam team("Test Team 1 - StrongOnes");
    team.addFighter(new Warrior("StrongWarrior", 50, 40, 80, 30));
    team.addFighter(new Warlock("StrongWarlock", 90, 20, 40, 60, 70));
    team.addFighter(new Warrior("VeryStrongWarrior", 70, 50, 90, 40));
    team.addFighter(new DeathKnight("StrongDeathKnight", 150, 100, 70, 50, 80));
    return team;
}

FightingTeam createTestFightingTeam2()
{
    FightingTeam team("Test Team 2 - NiceOnes");
    team.addFighter(new Warlock("NiceWarlock", 50, 40, 80, 30, 50));
    team.addFighter(new Warrior("NiceWarrior", 90, 20, 40, 60));
    team.addFighter(new DeathKnight("NiceDeathKnight", 70, 50, 90, 40, 50));
    team.addFighter(new DeathKnight("VeryNiceDeathKnight", 150, 100, 98, 90, 80));
    return team;
}

void testBattle()
{
    FightingTeam team1 = createTestFightingTeam1(), team2 = createTestFightingTeam2();
    Battle battle(&team1, &team2);
    battle.startBattle();
}

int main()
{
    testBattle();
    
    return 0;
}
