#include "Grid.h"
#include "Types.h"


Grid::Grid(int Lines, int Columns)
{
    xLenght = Lines;
    yLength = Columns;
    //Console.WriteLine("The battle field has been created\n");
    for (int i = 0; i < Lines; i++)
    {

        for (int j = 0; j < Columns; j++)
        {
            grids.push_back(Types::GridBox(i, j, false, (Columns * i + j)));
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
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* currentgrid = std::find(grids.begin(), grids.end(), yLength*i+j)._Ptr;
            if (currentgrid->ocupied)
                printf("[X]\t");
            else
                printf("[ ]\t");
        }
        printf("\n");
    }
    printf("\n");
}