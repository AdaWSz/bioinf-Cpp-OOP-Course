#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Cell.h"

class Grid {
    public: //methods
        Grid(long length, long height, long seed);
        void GenerateGrid();
        bool GetCell(long x, long y);
        int CountNeighbors(long x, long y); // Counts all alive cells around specified coordinates.
        void AdvanceTime();
        const std::vector<std::vector<Cell>>& GetData() const;

    private: //values
        const long sizeX;
        const long sizeY;
        const long seed;
        std::vector<std::vector<Cell>> data; //Binary matrix

};

#endif
