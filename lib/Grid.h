#ifndef GRID_H
#define GRID_H

#include "GridCell.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Represents the grid
class Grid {
    int gridSize;
    int minObjects;
    int maxObjects;
    std::vector<GridCellType> viableCellTypes;
    Pos startPos;
    Pos endPos;
    std::vector<std::vector<GridCell*>> gridCells; // 2D grid of cells

public:
    // Constructor
    Grid(int size, int minObjects, int maxObjects, std::vector<GridCellType> viableCellTypes);

    // Destructor
    ~Grid();

    // Generates the grid with random objects
    void generateGrid(const std::vector<GridCellType>& objectTypes);

    // Returns the ASCII representation of the grid
    std::string toASCII() const;

private:
    // Randomly place objects in the grid
    void dynamicallyGeneratePath(const std::vector<GridCellType>& objectTypes, Pos entry);

    // Randomly choose an entry position outside the grid
    Pos getEntryPosition() const;

    // Checks if a position is within the center square of the grid
    bool isWithinActualGrid(const Pos& pos) const;

    // Moves the ball in a direction until it exits the grid
    Pos simulateBallPath(const Pos& start, Direction direction);
};

#endif // GRID_H
