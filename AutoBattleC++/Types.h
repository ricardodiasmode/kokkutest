#pragma once
class Types
{
public:

    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;

        GridBox(int x, int y, bool InOcupied, int index)
        {
            xIndex = x;
            yIndex = y;
            ocupied = InOcupied;
            Index = index;
        }
        GridBox() {};

        inline bool operator==(const GridBox& rhs)
        {
            return this->Index == rhs.Index;
        }
        inline bool operator==(const int& rhs)
        {
            return this->Index == rhs;
        }
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

};

