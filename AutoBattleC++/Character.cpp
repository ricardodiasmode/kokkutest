#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

Character::Character(const Types::CharacterClass characterClass)
{
    const float MaxHealth = 120;
    const float MaxBaseDamage = 20;

    switch (characterClass)
    {
    case Types::CharacterClass::Paladin:
        this->SetHealth(MaxHealth * 0.8);
        this->SetBaseDamage(MaxBaseDamage * 0.8);
        this->SetIcon(*("P"));
        break;
    case Types::CharacterClass::Warrior:
        this->SetHealth(MaxHealth);
        this->SetBaseDamage(MaxBaseDamage * 0.6);
        this->SetIcon(*("W"));
        break;
    case Types::CharacterClass::Cleric:
        this->SetHealth(MaxHealth * 0.6);
        this->SetBaseDamage(MaxBaseDamage * 0.4);
        this->SetIcon(*("C"));
        break;
    case Types::CharacterClass::Archer:
        this->SetHealth(MaxHealth * 0.6);
        this->SetBaseDamage(MaxBaseDamage);
        this->SetIcon(*("A"));
        break;
    }

}

bool Character::TakeDamage(float amount, Grid* battlefield)
{
    Health -= BaseDamage;
	if (Health <= 0)
	{
		Die(battlefield);
		return true;
	}
	return false;
}

void Character::Die(Grid* battlefield)
{
    const bool AmIEnemy = PlayerIndex == 1;
    // Notification to user
   printf(AmIEnemy ? "\nYou lost! Game over.\n" : "\nYou are the best, you won!\n");
    // Since we have only 2 players, if 1 dies we end the game;
    exit(EXIT_SUCCESS);
}

void Character::WalkTo(Grid* battlefield, const int IndexToWalk)
{
    currentBox.ocupied = false;
    battlefield->grids[currentBox.Index] = currentBox;

    currentBox = battlefield->grids[IndexToWalk];
    currentBox.ocupied = true;
    battlefield->grids[currentBox.Index] = currentBox;
}

void Character::StartTurn(Grid* battlefield) {
    if (CheckCloseTargets(battlefield))
        Attack(Character::target, battlefield);
    else
    {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target

        if (currentBox.yIndex > target->currentBox.yIndex)
        {
            // Going left
            if(currentBox.yIndex > 0)
                WalkTo(battlefield, currentBox.Index - 1);
        }
        else if (currentBox.yIndex < target->currentBox.yIndex)
        {
            // Going right
            if (currentBox.yIndex < battlefield->yLength-1)
                WalkTo(battlefield, currentBox.Index + 1);
        }
        else if (currentBox.xIndex > target->currentBox.xIndex)
        {
            printf("\nGoing up. xIdx: %d\n", currentBox.xIndex);
            // Going up
            if (currentBox.xIndex > 0)
                WalkTo(battlefield, currentBox.Index - battlefield->xLength);
        }
        else if (currentBox.xIndex < target->currentBox.xIndex)
        {
            printf("\nGoing down. xIdx: %d\n", currentBox.xIndex);
            // Going down
            if (currentBox.xIndex < battlefield->xLength-1)
                WalkTo(battlefield, currentBox.Index + battlefield->xLength);
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    const int UpGridIndex = currentBox.Index - battlefield->xLength;
    const int DownGridIndex = currentBox.Index + battlefield->xLength;
    const bool ShouldCountDown = DownGridIndex+1 < battlefield->xLength * battlefield->yLength;
    const int LeftGridIndex = currentBox.Index - 1;
    const int RightGridIndex = currentBox.Index + 1;
    const bool ShouldCountRight = RightGridIndex + 1 < battlefield->xLength * battlefield->yLength;

    // Whether or not has a enemy around
    Types::GridBox* UpGrid = std::find(battlefield->grids.begin(), battlefield->grids.end(), UpGridIndex)._Ptr;
    Types::GridBox* DownGrid = std::find(battlefield->grids.begin(), battlefield->grids.end(), DownGridIndex)._Ptr;
    Types::GridBox* LeftGrid = std::find(battlefield->grids.begin(), battlefield->grids.end(), LeftGridIndex)._Ptr;
    Types::GridBox* RightGrid = std::find(battlefield->grids.begin(), battlefield->grids.end(), RightGridIndex)._Ptr;

    if (UpGrid->xIndex > 0)
    {
        if (UpGrid->ocupied)
            return true;
    }
    if (ShouldCountDown && DownGrid->xIndex < battlefield->xLength - 1)
    {
        if (DownGrid->ocupied)
            return true;
    }
    if (LeftGrid->yIndex > 0)
    {
        if (LeftGrid->ocupied)
            return true;
    }
    if (ShouldCountRight && RightGrid->yIndex < battlefield->yLength - 1)
    {
        if (RightGrid->ocupied)
            return true;
    }

    return false;
}

void Character::Attack(Character* target, Grid* battlefield)
{
    target->TakeDamage(GetBaseDamage(), battlefield);
}

