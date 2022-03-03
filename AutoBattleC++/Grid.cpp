#include "Grid.h"
#include "Types.h"
#include "BattleField.h"


Grid::Grid(int Lines, int Columns, BattleField* Inbattlefield)
{
    battlefield = Inbattlefield;

    xLength = Lines;
    yLength = Columns;
    //Console.WriteLine("The battle field has been created\n");
    int CurrentGridIndex = 0;
    for (int i = 0; i < Lines; i++)
    {

        for (int j = 0; j < Columns; j++)
        {
            grids.push_back(Types::GridBox(i, j, false, CurrentGridIndex));
            CurrentGridIndex++;
            //Console.Write($"{newBox.Index}\n");
        }
    }
	//drawBattlefield(Lines, Columns);
}

Grid::~Grid() 
{

}

void Grid::drawBattlefield(int Lines, int Columns)
{
    int CurrentGridIndex = 0;
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* currentgrid = std::find(grids.begin(), grids.end(), CurrentGridIndex)._Ptr;
            CurrentGridIndex++;
            if (currentgrid->ocupied)
            {
                const bool IsEnemy = (currentgrid->Index != battlefield->PlayerCharacter.get()->GetCurrentBox().Index);
                char CurrentIcon = IsEnemy ?
                    battlefield->EnemyCharacter.get()->GetIcon() : battlefield->PlayerCharacter.get()->GetIcon();
                printf("[%c]\t", CurrentIcon);
            }
            else
                printf("[ ]\t");
        }
        printf("\n");
    }
    printf("\n");
}