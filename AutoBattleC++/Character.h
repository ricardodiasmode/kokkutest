#pragma once
#include "Grid.h"
#include "Character.h"
#include "Types.h"

class Character
{
private:
    float Health;
    float BaseDamage;
    int PlayerIndex;

    Character* target;

    bool IsDead;
    char Icon;

    Types::GridBox currentBox;
public:

    Character(const Types::CharacterClass characterClass);
    
    bool TakeDamage(float amount, Grid* battlefield);

    void Die(Grid* battlefield);

    void WalkTo(Grid* battlefield, const int IndexToWalk);

    void StartTurn(Grid* battlefield);

    bool CheckCloseTargets(Grid* battlefield);

    void Attack(Character* target, Grid* battlefield);

    // Set Functions
    inline void SetHealth(const float HealthToSet) { Health = HealthToSet; }
    inline void SetBaseDamage(const float BaseDamageToSet) { BaseDamage = BaseDamageToSet; }
    inline void SetPlayerIndex(const int PlayerIndexToSet) { PlayerIndex = PlayerIndexToSet; }
    inline void SetTarget(Character* TargetToSet) { target = TargetToSet; }
    inline void SetIsDead(const bool IsDeadToSet) { IsDead = IsDeadToSet; }
    inline void SetIcon(const char IconToSet) { Icon = IconToSet; }
    inline void SetCurrentBox(const Types::GridBox currentBoxToSet) { currentBox = currentBoxToSet; }

    // Get Functions
    inline const float GetHealth() { return Health; }
    inline const float GetBaseDamage() { return BaseDamage; }
    inline const int GetPlayerIndex() { return PlayerIndex; }
    inline Character* GetTarget() { return target; }
    inline const bool GetIsDead() { return IsDead; }
    inline const char GetIcon() { return Icon; }
    inline const Types::GridBox GetCurrentBox() { return currentBox; }

};

