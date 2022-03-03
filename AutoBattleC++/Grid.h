#pragma once
#include <Vector>
#include "Types.h"

class BattleField;

class Grid
{

public:

    Grid(int Lines, int Columns, BattleField* Inbattlefield);
    ~Grid();

    BattleField* battlefield;
    std::vector<Types::GridBox> grids;

    int xLength;
    int yLength;
    
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield();
};

