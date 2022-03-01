#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>

BattleField::BattleField() {
    
    grid = new Grid(5, 5);
    AllPlayers = new list<Character>();
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

    std::getline(std::cin, choice);
    
    std::cin >> choice;
    switch (choice.c_str())
    {
    case "1":
        CreatePlayerCharacter(stoi(choice));
        break;
    case "2":
        CreatePlayerCharacter(stoi(choice));
        break;
    case "3":
        CreatePlayerCharacter(stoi(choice));
        break;
    case "4":
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
    Types::CharacterClass* characterClass = (Types::CharacterClass*)classIndex;
    printf("Player Class Choice: {characterClass}");
    
    PlayerCharacter = std::make_shared<Character>(characterClass);
    
    PlayerCharacter->SetHealth(100);
    PlayerCharacter->SetBaseDamage(20);
    PlayerCharacter->SetPlayerIndex(0);

    CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    
    int randomInteger = 1 + rand() % 4;
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;
    printf("Enemy Class Choice: {enemyClass}");
    EnemyCharacter = std::make_shared<Character>(enemyClass);
    EnemyCharacter->SetHealth(100);
    PlayerCharacter->SetBaseDamage(20);
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

void BattleField::StartTurn() {

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    std::list<shared_ptr<Character>>::iterator it;

    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {
        it->get()->StartTurn(grid);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->GetHealth() == 0)
    {
        return;
    }
    else if (EnemyCharacter->GetHealth() == 0)
    {
        printf("\n");

        // endgame?

        printf("\n");

        return;
    }
    else
    {
        printf("\n");
        printf("Click on any key to start the next turn...\n");
        printf("\n");

        //TODO
        //ConsoleKeyInfo key = Console.ReadKey();
        StartTurn();
    }
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
        grid->drawBattlefield(5, 5);
    }
    else
    {
        AlocateEnemyCharacter();
    }


}