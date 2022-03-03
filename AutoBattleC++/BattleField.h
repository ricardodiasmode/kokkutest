#pragma once
#include "Character.h"
#include "Types.h"
#include <list>
#include <iostream>
#include "Grid.h"
using namespace std;
class BattleField
{
public:

	BattleField();

	Grid* grid;
	Types::GridBox* PlayerCurrentLocation;
	Types::GridBox* EnemyCurrentLocation;
	list<shared_ptr<Character>>* AllPlayers;
	shared_ptr<Character> PlayerCharacter;
	shared_ptr<Character> EnemyCharacter;
	int currentTurn;

	void Setup();

	void GetPlayerChoice();

	void CreatePlayerCharacter(int classIndex);

	void CreateEnemyCharacter(const int PlayerClassIndex);

	void StartGame();

	void StartTurn();

	void HandleTurn();

	void AlocatePlayers();

	void AlocatePlayerCharacter();

	void AlocateEnemyCharacter();
};


