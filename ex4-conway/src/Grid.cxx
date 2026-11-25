#include "Grid.h"
#include <random>
#include <stdexcept>
#include <iostream>

Grid::Grid(long length, long height, long userseed):
    sizeX(length),
    sizeY(height),
    seed(userseed)
{}


void Grid::GenerateGrid() {
    std::mt19937 rng(seed);
    std::bernoulli_distribution life(0.3); //modifiable
    data = std::vector<std::vector<Cell>>(sizeX, std::vector<Cell>(sizeY));

    bool isAlive;
    for (std::vector<Cell>& row : data) {
        for (Cell& cell: row) {
            isAlive = life(rng);
            if (isAlive)
                cell.SetAlive();
            else
                cell.SetDead();
        }
    }
}

bool Grid::GetCell(long x, long y) {
    if (x < data.size() && y < data[0].size())
        return data[x][y].GetStatus();
    else
        throw std::runtime_error("Coordinates x: " + std::to_string(x) + " y: " + std::to_string(y) + "are out of bounds");
    return false;
}

int Grid::CountNeighbors(long x, long y) {
    int aliveCount = 0;

    try {
        bool boundsCheck = GetCell(x,y);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 0;
    }

    for (long i=x-1; i <= x+1; ++i) {
           for (long j = y-1; j <= y+1; ++j) {
               if (i == x && j == y)
                   continue;
               else if (i < 0 || j < 0 || i >= data.size() || j >= data[0].size())
                   continue;
               else
                   aliveCount += static_cast<int>(data[i][j].GetStatus());
           }
    }
    return aliveCount;
}


void Grid::AdvanceTime() {
    bool cellStatus;
    int neighbors;
    std::vector<std::vector<Cell>> dataNextGen(sizeX, std::vector<Cell>(sizeY));
    for (long x = 0; x < data.size(); ++x) {
        for (long y = 0; y < data[x].size(); ++y) {
            neighbors = CountNeighbors(x, y);
            cellStatus = data[x][y].DetermineLife(neighbors);

            if (cellStatus)
                dataNextGen[x][y].SetAlive();
            else
                dataNextGen[x][y].SetDead();
        }
    }
    data = dataNextGen;
}

const std::vector<std::vector<Cell>>& Grid::GetData() const {
    return data;
}
