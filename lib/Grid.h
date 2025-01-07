#ifndef GRID_H
#define GRID_H

#include <vector>
#include <set>
#include <string>
#include <utility>
#include "GridCell.h"

// Type alias for position in the grid (row, column)
using Pos = std::pair<int, int>;

// Enumeration for the direction of the ball
enum class Direction {
    Up,
    Down,
    Left,
    Right,
    None
};

class Grid {
public:
    int gridSize;                                  // Size of the grid
    int minObjects;                                // Minimum number of objects to place
    int maxObjects;                                // Maximum number of objects to place
    Pos entryPos;
    std::vector<GridCellType> objectTypes;         // Types of grid objects
    std::vector<std::vector<GridCell*>> gridCells; // 2D grid of cells

    // Constructor
    Grid(int gridSize, int minObjects, int maxObjects, const std::vector<GridCellType>& objectTypes);

    // Destructor
    ~Grid();

    // Generates the grid dynamically
    void generateGrid(std::vector<GridCellType>& objectTypes);

private:

    // Helper functions
    void initializeGrid();
    Pos getEntryPosition() const;
    Direction getStartingDirection(const Pos& entryPos);
    bool isWithinBounds(Pos& pos);
    Direction getNewDirection(GridCellType type, Direction currentDirection, Orientation orientation, Pos);
    std::vector<Pos> findOpenPositions(const Pos& currentPos, Direction currentDirection, const std::set<Pos>& occupied);
    std::vector<Orientation> getViableOrientations(GridCellType type);
    Pos getNextPosition(const Pos& currentPos, Direction direction);
    bool isOutOfCenter(const Pos& pos);
    std::string Grid::toASCII() const;
};

#endif // GRID_H
