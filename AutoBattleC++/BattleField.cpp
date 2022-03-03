#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <conio.h>
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>

BattleField::BattleField() {
    
    grid = new Grid(5, 7, this);
    AllPlayers = new list<shared_ptr<Character>>();
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->grids.size();
    //Setup();
}

void BattleField::Setup()
{
    GetPlayerChoice();
}

void BattleField::GetPlayerChoice()
{
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");
    //store the player choice in a variable
    std::string choice;
    
    std::cin >> choice;
    switch (stoi(choice))
    {
    case 1:
        CreatePlayerCharacter(stoi(choice));
        break;
    case 2:
        CreatePlayerCharacter(stoi(choice));
        break;
    case 3:
        CreatePlayerCharacter(stoi(choice));
        break;
    case 4:
        CreatePlayerCharacter(stoi(choice));
        break;
    default:
        printf("You must type a valid number\n");
        GetPlayerChoice();
        break;
    }
}

void BattleField::CreatePlayerCharacter(int classIndex)
{
    Types::CharacterClass characterClass = (Types::CharacterClass)classIndex;

    char ClassToChar;
    switch (classIndex)
    {
    case 1:
        ClassToChar = *"P";
        break;
    case 2:
        ClassToChar = *"W";
        break;
    case 3:
        ClassToChar = *"C";
        break;
    case 4:
        ClassToChar = *"A";
        break;
    }
    printf("Player Class Choice: {%c}\n", ClassToChar);
    
    PlayerCharacter = std::make_shared<Character>(characterClass);

    PlayerCharacter->SetPlayerIndex(0);

    CreateEnemyCharacter(classIndex);

}

void BattleField::CreateEnemyCharacter(const int PlayerClassIndex)
{
    //randomly choose the enemy class and set up vital variables
    
    int randomInteger = PlayerClassIndex;
    while(randomInteger == PlayerClassIndex)
       randomInteger = 1 + rand() % 4;
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;

    char ClassToChar;
    switch (randomInteger)
    {
    case 1:
        ClassToChar = *"P";
        break;
    case 2:
        ClassToChar = *"W";
        break;
    case 3:
        ClassToChar = *"C";
        break;
    case 4:
        ClassToChar = *"A";
        break;
    }

    printf("Enemy Class Choice: {%c}\n", ClassToChar);
    EnemyCharacter = std::make_shared<Character>(enemyClass);

    PlayerCharacter->SetPlayerIndex(1);
    StartGame();
}

void BattleField::StartGame()
{
    //populates the character variables and targets
    EnemyCharacter->SetTarget(PlayerCharacter.get());
    PlayerCharacter->SetTarget(EnemyCharacter.get());
    AllPlayers->push_back(PlayerCharacter);
    AllPlayers->push_back(EnemyCharacter);
    AlocatePlayers();
    StartTurn();
}

void BattleField::StartTurn() 
{
    if (currentTurn == 0)
        AllPlayers->sort();

    std::list<shared_ptr<Character>>::iterator it;

    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {
        it->get()->StartTurn(grid);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    grid->drawBattlefield();
    printf("Turn %d finished. Click on any key to start the next turn...\n", currentTurn);
    printf("\n");

    _getch();
    StartTurn();
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();
}

void BattleField::AlocatePlayerCharacter()
{
    int random = 0;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;

    if (!RandomLocation->ocupied)
    {
        //Types::GridBox* PlayerCurrentLocation = RandomLocation;
        PlayerCurrentLocation = &*l_front;
        l_front->ocupied = true;
        PlayerCharacter->SetCurrentBox(*l_front);
        AlocateEnemyCharacter();
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    int random = 24;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;
    
    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = &*l_front;
        l_front->ocupied = true;
        EnemyCharacter->SetCurrentBox(*l_front);
    }
    else
    {
        AlocateEnemyCharacter();
    }
}